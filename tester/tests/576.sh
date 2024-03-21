export A=hey
export A B=Hola D E C="Que Tal"
echo $PROUT$B$C > /tmp/a > /tmp/b > /tmp/c
cat /tmp/a
cat /tmp/b
cat /tmp/c
