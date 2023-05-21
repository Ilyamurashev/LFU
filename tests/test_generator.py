from random import randint
### settings

#cache size range
cache_lower_limit = 1
cache_upper_limit = 100
#page count range
num_min = 10
num_max = 1000
#page number range
page_range_min = 10
page_range_max = 100

###
m = randint(cache_lower_limit, cache_upper_limit) #cache size
n = randint(num_min, num_max) #number of pages

f = open('test1.txt', 'w')
try:
    f.write(str(m))
    f.write(' ')
    f.write(str(n))
    f.write(' ')
    for i in range(n):
        page = randint(page_range_min, page_range_max)
        f.write(str(page))
        f.write(' ')

finally:
    f.close()
