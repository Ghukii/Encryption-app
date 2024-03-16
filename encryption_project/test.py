import cyphers

T = cyphers.Transpose_cypher('phrasejfjfvs', 3412, 'encrypt')

print(T.get_result())

key = '341254'

s = set(list(range(1, len(key) + 1)))

for i in key:
    s.add(int(i))

print(s)