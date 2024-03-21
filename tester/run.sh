# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 13:41:27 by lcottet           #+#    #+#              #
#    Updated: 2024/03/21 19:05:57 by lcottet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

RED="\e[31m"
BLUE="\e[34m"
YELLOW="\e[33m"
MAGENTA="\e[35m"
GREEN="\e[32m"
CYAN="\e[36m"
ENDCOLOR="\e[0m"

TESTS=$(ls -v1 ./tests/*.sh)

NB_TEST=$(echo $TESTS | wc -l )
echo -e $'\n\n\n\n'"${YELLOW}Running $NB_TEST tests...${ENDCOLOR}"

OG_PWD=$(pwd)
for filename in $TESTS; do
	CMD=$(cat $filename)$'\n'pwd$'\n'exit
	echo -n -e $'\n'"${CYAN}Running test${ENDCOLOR} $filename"
	rm -rf exec_env
	mkdir -p exec_env
	cd exec_env && LD_PRELOAD=$OG_PWD/force_tty.so bash 2> ../bash_outputs/err 1> ../bash_outputs/out < ../$filename
	cd ..
	BASH_EXIT=$?
	rm -rf exec_env
	mkdir -p exec_env
	cd exec_env && ../../minishell 2> ../user_outputs/err 1> ../user_outputs/out < ../$filename
	cd ..
	USER_EXIT=$?
	OUT_DIFF=$(diff bash_outputs/out user_outputs/out)
	ERR_DIFF=$(diff bash_outputs/err user_outputs/err)
	if [ "$OUT_DIFF" != "" ]; then
		echo -e " ${RED}KO${ENDCOLOR}"
		echo "OUTPUT DIFF:"
		echo "$OUT_DIFF"
		exit 1
	elif [ "$(cat user_outputs/err | wc -l)" != "$(cat bash_outputs/err | uniq -w 14 | wc -l)" ]; then
		echo -e " ${RED}KO${ENDCOLOR}"
		echo "ERROR DIFF:"
		echo "$ERR_DIFF"
		exit 1
	elif [ "$BASH_EXIT" != "$USER_EXIT" ]; then
		echo -e " ${RED}KO${ENDCOLOR}"
		echo "EXIT CODE DIFF:"
		echo "Expected: $BASH_EXIT"
		echo "Got: $USER_EXIT"
		exit 1
	else
		echo -e " ${GREEN}OK${ENDCOLOR}"
	fi
	rm user_outputs/err user_outputs/out bash_outputs/err bash_outputs/out
done