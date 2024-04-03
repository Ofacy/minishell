# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 13:41:27 by lcottet           #+#    #+#              #
#    Updated: 2024/04/03 18:39:56 by lcottet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

OUTPUT_EXIT=1
ERROR_EXIT=1
STATUS_EXIT=1

RED="\e[31m"
BLUE="\e[34m"
YELLOW="\e[33m"
MAGENTA="\e[35m"
GREEN="\e[32m"
CYAN="\e[36m"
ENDCOLOR="\e[0m"

TESTS=$(ls -v1 tests/*.sh)

NB_TEST=$(echo "$TESTS" | wc -l)
echo -e $'\n\n\n\n'"${YELLOW}Running $NB_TEST tests...${ENDCOLOR}"

mkdir -p bash_outputs
mkdir -p user_outputs
OG_PWD=$(pwd)
for filename in $TESTS; do
	CMD=$(cat $filename)$'\n'pwd$'\n'exit
	echo -n -e $'\n'"${CYAN}Running test${ENDCOLOR} $filename"
	rm -rf exec_env
	mkdir -p exec_env
	cd exec_env && echo "$CMD" | bash 2> ../bash_outputs/err 1> ../bash_outputs/out
	cd ..
	BASH_EXIT=$?
	rm -rf exec_env
	mkdir -p exec_env
	cd exec_env && echo "$CMD" | ../../minishell 2> ../user_outputs/err 1> ../user_outputs/out
	cd ..
	USER_EXIT=$?
	OUT_DIFF=$(diff -U 3 bash_outputs/out user_outputs/out)
	ERR_DIFF=$(diff -U 3 bash_outputs/err user_outputs/err)
	if [ "$OUTPUT_DIFF" != "" ]; then
		echo -e " ${RED}KO${ENDCOLOR}"
		echo "OUTPUT DIFF:"
		echo "$OUT_DIFF"
		if [[ "$OUTPUT_EXIT" -eq 1 ]]; then
			exit 1
		fi
	elif [ "$(cat user_outputs/err | wc -l)" != "$(cat bash_outputs/err | uniq -w 14 | wc -l)" ]; then
		echo -e " ${RED}KO${ENDCOLOR}"
		echo "ERROR DIFF:"
		echo "$ERR_DIFF"
		if [[ "$ERROR_EXIT" -eq 1 ]]; then
			exit 1
		fi
	elif [ "$BASH_EXIT" != "$USER_EXIT" ]; then
		echo -e " ${RED}KO${ENDCOLOR}"
		echo "EXIT CODE DIFF:"
		echo "Expected: $BASH_EXIT"
		echo "Got: $USER_EXIT"
		if [[ "$STATUS_EXIT" -eq 1 ]]; then
			exit 1
		fi
	else
		echo -e " ${GREEN}OK${ENDCOLOR}"
	fi
	rm user_outputs/err user_outputs/out bash_outputs/err bash_outputs/out
done
