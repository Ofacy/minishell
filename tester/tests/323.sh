mkdir a
mkdir a/b
cd a/b
rm -r ../../a
cd
echo $PWD
echo $OLDPWD
