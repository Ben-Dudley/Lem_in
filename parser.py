f = open('del')
line = f.readline()
res = {}
errors = {}
while line:
    tmp = line.split(" ")[1]
    try:
        res[tmp] += 1
        if (res[tmp]>2):
            errors[tmp] = res[tmp]
    except:
        res[tmp] = 1
    
    line = f.readline()
f.close()

for k in res:
    if (res[k] != 2):
        errors[k] = res[k]

print(errors)

# {'Olz0': 8, 'U_s5': 8}