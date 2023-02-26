import csys


file = 'main.py'


csys.system('lsd -l')
if csys.isexists(file):
    # csys.__flushostream()
    print('test.py permissions: {' + csys.getperms('main.py') + '}')
else:
    print('TEsdfgsdfgsdfgST', 9)
