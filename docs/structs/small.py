f = open('graph.dot')

def find_between( s, first, last ):
    try:
        start = s.index( first ) + len( first )
        end = s.index( last, start )
        return s[start:end]
    except ValueError:
        return ""

s1 = "digraph "
s2 = """
{
graph [ rankdir="RL" ]
"""

s3 = "}"

for line in f:
	name = find_between(line, 'label="', '\\n')

	g = open(name+'.dot', 'w')

	res = s1 + name + s2 + line + s3

	g.write(res)

	g.close()

f.close()