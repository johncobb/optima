
str_val = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ"

base = 33
vin = "JTH"
vrad = 0
vrad_log = 0
exp = 0
l_val = 0
i = 0

for x in vin:
    l_val = str_val.index(x) + 1
    
    exp = (len(vin)-1) - i
    vrad_log = ((l_val) * pow(base, exp))
    vrad += (l_val * pow(base, exp))
    
    print("[", i, "][", l_val, "][", x, "]", base, "^", exp, "=", vrad_log, "+=", vrad)
    i = i + 1

print(vrad)

JTHKD5BH0D2170008

# return sum([x[0] * x[1] for x in zip([transliterationString.find(c) % 10 for c in vin], valWeights)]) % 11