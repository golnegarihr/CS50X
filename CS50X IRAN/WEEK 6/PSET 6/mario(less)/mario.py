from cs50 import get_int

#  First get height and then check number so, if was not between 1 and 8  then repet  this step ;
#  then show the sharp sing and space according to number of height ;
#
#  for instance if get 4 height show this result:
#     #
#    ##
#   ###
#  ####


height = 0

while height < 1 or height > 8:

    height = get_int("enter height  Size : ")

dot = 0
sharp = 0
dot = height - 1
sharp = height - dot

for i in range(height):

    print(" " * dot + "#" * sharp)
    sharp += 1
    dot -= 1