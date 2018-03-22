n = int(input("Введите N: "))
k = int(input("Введите k: "))
first_n = n

ar = [1 for i in range(n)]

curPos = 0
i = 0

while n != 0:
	# print('curPos:', curPos%first_n)
	if ar[curPos%first_n] != 0:
		result = curPos%first_n
		i += 1
		if i == k:
			ar[curPos%first_n] = 0
			i = 0
			n -= 1
	print(ar)
	print()
	curPos += 1
print(curPos)
print(result+1)
