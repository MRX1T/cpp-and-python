import csys


file = 'test.py'


csys.system('lsd -l')
if csys.isexists(file):
    print('test.py permissions: ', csys.getperms('dfs'))
else:
    pass
