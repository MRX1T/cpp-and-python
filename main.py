import csys


file = 'main.py'


csys.system('lsd -l')
if csys.isexists(file):
    print('test.py permissions: {' + csys.getperms('maingj.py') + '}')
else:
    print('TEsdfgsdfgsdfgST', 9)
