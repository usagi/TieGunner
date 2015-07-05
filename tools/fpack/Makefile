#---------------------------------------------------------------#
#   Copyright 2003 (c) Hiramatsu Kunihito All rights reserved.	#
#   E-Mail: hira@din.or.jp                                      #
#...............................................................#
#   TARGET:     �������å�̾                                    #
#   xSOURCE:    �������ե�����                                  #
#      ���������֥������Ȥ��ɲä�����ϡ����Υ������Ȥʤ�     #
#      �ե�����̾�� "xSOURCE" ���ɲä��ơ�"make depend"  ��     #
#      �Ȥ��롢��������°��§�ϡ�"Makefile"�κǸ���ɲä���     #
#      �롣							#
#   DFLAGS:	�Ķ��ѿ�������					#
#   LIBNAME:	�饤�֥�꡼�λ���				#
#   �����Ρ�Makefile��ή�Ѥ����硢��#=== ... ===#�פޤ���	#
#   �ꤹ����ɤ��褦�ˤʤäƤ��롣				#
#...............................................................#
#   February,   5, 2003:     Version 0.10                       #
#---------------------------------------------------------------#
TARGET	=	fpack
ASOURCE	=
CSOURCE	=	main.c	\
		hash.c	\
		misc.c

#   "makedepend" �˥��ץ������Ϥ���褦�ˡ�"DFLAGS" �ˤϡ�"-D" �Τ߻��ꡣ
DFLAGS	=

#  �饤�֥�꡼̾���
LIBNAME	=	

#  Warnning ����ե饰
WNFLAGS	=	error implicit return-type switch format
#WNFLAGS	=	error implicit return-type unused switch format
# WNFLAGS	=	error all

#===============================================================#
#   include / library path, loading library.			#
#===============================================================#

#   �饤�֥�꡼�Υ�󥯤ν��֤����פʤΤ����դ������
STDLIB	=	$(addprefix -l, $(LIBNAME))

#   ���֥������ȥե�����̾�ϡ��ʲ��Υ롼��ˤ�롣
OBJECTS	=	$(ASOURCE:.s=.o) $(CSOURCE:.c=.o)

#
#   Compiler, Linker Options, Resource_compiler.
#
AS	=	gcc
CC	=	gcc
CPP	=	gcc
LD	=	gcc
DEL	=	rm -f

AFLAGS	=
CFLAGS	=	-O2
PFLAGS	=
LFLAGS	=

CFLAGS +=	$(DFLAGS)

CWARNS	=	$(addprefix -W, $(WNFLAGS))

.SUFFIXES:
.SUFFIXES: .s .h .c .cpp .o

#   Ʊ̾�ե�����Ȥξ��ͤ��򤱤뤿��Υ������åȻ���
.PHONY: clean depend test


$(TARGET): $(OBJECTS) Makefile
	$(LD) $(LFLAGS) -o $(TARGET) $(STDLIB) $(OBJECTS) 

.s.o:
	$(AS) $(AFLAGS) -c $< -o $@

.c.o:
	$(CC) $(COPT) $(CFLAGS) $(CWARNS) -c $< -o $@

.cpp.o:
	$(CPP) $(POPT) $(PFLAGS) -c $< -o $@

#   ̵�������ѥ���ȥ꡼
all: $(TARGET)
	make clean
	make depend

#   ���֥������Ȥξõ��ѥ���ȥ꡼
clean:
	$(DEL) $(OBJECTS)
	$(DEL) $(TARGET)

#   ��°��§�����ѥ���ȥ꡼
depend:
	makedepend -Y -- $(DFLAGS) -- $(ASOURCE) $(CSOURCE)

#    �ƥ���
test:
	cat test.lst | ./fpack test.pak

#   ��̩�ʸġ��ν�°��§

# DO NOT DELETE

main.o: default.h hash.h misc.h main.h
hash.o: default.h hash.h main.h
misc.o: default.h misc.h