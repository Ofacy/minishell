mkdir a
mkdir a/b
cd a/b
rm -r ../../a
echo $PWD
echo $OLDPWD
