#include <stdio.h>
#include <unistd.h>

static inline void sub_str(char *dest, char *src, int, int);
static inline void asm_sub_str(char *dest, char *src, int, int);

int main(){

char s[100], d[100], f[100];
int sidx, eidx, n;

printf("Enter String(100 chars max) :\n");
n = read(0, s, 100);
s[n-1] = '\0';

printf("Enter start index :");
scanf("%d", &sidx);
if(sidx<0 || sidx>n-1){
	printf("Invalid start index\n");
	return 0;
	}
printf("Enter end index :");
scanf("%d", &eidx);
if(eidx<sidx || sidx>n-1){
	printf("Invalid end index\n");
	return 0;
	}
printf("\n-----using inline asm code-----\n");
printf("before: s=[%s] d=[%s]\n",s,d);
asm_sub_str(d,s,sidx,eidx);
printf("after:  s=[%s] d=[%s]\n",s,d);

printf("\n-----using normal c code-------\n");
printf("before: s=[%s] f=[%s]\n",s,f);
sub_str(f,s,sidx,eidx);
printf("after:  s=[%s] f=[%s]\n",s,f);

return 0;
}

void asm_sub_str(char *dst, char *src, int sidx, int eidx){
int rsrc, rdst;

__asm__ __volatile__(
	 "add $1, %3\n" //eidx+1
	 "add %2, %0\n" //add sidx to src 
	 "sub %2, %3\n" //eidx=eidx-sidx(count)
	 "1:\tlodsb\n;"
	 "stosb\n;"
	 "dec %3\n"	//decrement count
	 "jnz 1b;\n"
	 "xor %%eax,%%eax\n"//null in eax
	 "stosb\n"	//store null at the end of the substring
	 : "=&S" (rsrc), "=&D" (rdst)
	   //%0 esi	 %1 edi
	 : "r" (sidx), "r" (eidx), "0" (src),"1" (dst) 	
	   //%2		%3	    %4		%5	 
	  );
}

void sub_str(char *dst, char *src, int sidx, int eidx){
int count = eidx-sidx+1;
for(int i = 0; i<count; i++){
	dst[i] = src[sidx+i];
	}
}
