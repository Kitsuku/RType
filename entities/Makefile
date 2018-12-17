##
## EPITECH PROJECT, 2018
## rtype
## File description:
## 
##

RM 	= rm -rf

MK 	= make -C

all:
	$(MK) plane/
	$(MK) alien/

clean:
	$(MK) plane/ clean
	$(MK) alien/ clean

fclean: clean
	$(RM) Plane.so
	$(RM) Alien.so

re: fclean all