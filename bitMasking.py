A = 69; i = 3 #Examples
# Consider 0-indexed representation for the following with 0 being the far right digit/element, thus :
# i ranges from 0 to len(A) - 1:

# Check if i'th bit is set of A: 
result = A & (1 << i)

#Set i´th bit to ON :
A |= A (1 << i)

#Clear i'th bit ( turn OFF ):
A &= A & ~(1 << i)

#Dividing/Multiplying by 2^n:
n = 3

A / (2**n) == A >> n
A * (2**n) == A << n

#Check if 2**n divides A:
def divsible(A):
  for i in range(n):
    if A & (1 << i):
      return False
  return True
  
# i'th element in the Grey Code Sequence :
greycodeI = i ^ (i>>1)




