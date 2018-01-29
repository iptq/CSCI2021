import os

def nextrand()

def check(cookie):
	if not(cookie >> 28): return False
	if cookie == 10: return False
	x = 8
	while (cookie >> x) != 10:
		x += 8
		if x == 32:
			return True
	return False

def hash(string):
	result = 0
	for i in range(len(string)):
		result = ord(string[i]) + 103 * result
	return result

def gencookie(username):
	seed = hash(username)
	rand = LCG(seed)
	cookie = rand.next()
	while not check(cookie):
		cookie = rand.next()
	return cookie


print "0x%08x" % gencookie("lol")      # 0x3cc6936f
print "0x%08x" % gencookie("zhan4854") # 0x5245f0fd