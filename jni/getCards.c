#include "com_example_twentyfour_JniClient.h"

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define DIV(x,y) ((x)%(y)==0)

#define MAX 512
char formulas[MAX][32];

char result[512];
int len = 0;

void sort(int a[], int n) {
	// 对整数数组 a[n] (2<= n <=4) 按从大到小排序
	int i, j, t;
	if (n >= 5 || n <= 1)
		return;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (a[i] < a[j]) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
}

int exist(char* formula) {
	int i;
	for (i = 0; i < MAX; i++) {
		if (formulas[i][0] == '\0') { // 比较到空字符串位置，说明不存在，返回空位置索引
			return i;
		} else if (strcmp(formula, formulas[i]) == 0) {
			return -1; // 已经存在
		}
	}
	return -1;
}

int check2(char* formula, int x, int y, int u, int v) {
	int index;
	int a[4];
	char buf[256];
	int sum[2];
	int multiple[2];
	int delta[2];
	a[0] = x, a[1] = y, a[2] = u, a[3] = v;
	if (strcmp(formula, "++++") == 0) {
		sort(a, 4);
		sprintf(buf, "++++%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "+++-") == 0) {
		sort(a, 3);
		sprintf(buf, "+++-%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "++--") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "++--%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(+)*(-)") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "(+)*(-)%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(*-)/") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "(*-)/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(+-)*") == 0) {
		sort(a, 2);
		sprintf(buf, "(+-)*%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(+)*(+)") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sum[0] = a[0] + a[1]; // 同时对 和 以及 加数 排序
		sum[1] = a[2] + a[3];
		if (sum[0] > sum[1])
			sprintf(buf, "(+)*(+)%d%d%d%d%d%d", sum[0], a[0], a[1], sum[1],
					a[2], a[3]);
		else
			sprintf(buf, "(+)*(+)%d%d%d%d%d%d", sum[1], a[2], a[3], sum[0],
					a[0], a[1]);
	} else if (strcmp(formula, "(*-)*") == 0) {
		sort(a, 2);
		sprintf(buf, "(*-)*%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*--") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "*--%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*+*") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		multiple[0] = a[0] * a[1];
		multiple[1] = a[2] * a[3];
		if (multiple[0] > multiple[1])
			sprintf(buf, "*+*%d%d%d%d%d%d", multiple[0], a[0], a[1],
					multiple[1], a[2], a[3]);
		else
			sprintf(buf, "*+*%d%d%d%d%d%d", multiple[1], a[2], a[3],
					multiple[0], a[0], a[1]);
	} else if (strcmp(formula, "*-*") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "*-*%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(-)**") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "(-)**%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(++)*") == 0) {
		sort(a, 3);
		sprintf(buf, "(++)*%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "**/") == 0) {
		sort(a, 3);
		sprintf(buf, "**/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*+-") == 0) {
		sort(a, 2);
		sprintf(buf, "*+-%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(-)*(-)") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		delta[0] = a[0] - a[1];
		delta[1] = a[2] - a[3];
		if (delta[0] > delta[1]) // 因子大的放在前面
			sprintf(buf, "(-)*(-)%d%d%d%d%d%d", delta[0], a[0], a[1], delta[1],
					a[2], a[3]);
		else
			sprintf(buf, "(-)*(-)%d%d%d%d%d%d", delta[1], a[2], a[3], delta[0],
					a[0], a[1]);
	} else if (strcmp(formula, "/++") == 0) {
		sort(&a[2], 2);
		sprintf(buf, "/++%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(+)*/") == 0) {
		sort(a, 2);
		sprintf(buf, "(+)*/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*/+") == 0) {
		sort(a, 2);
		sprintf(buf, "*/+%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*/(-)") == 0) {
		sort(a, 2);
		sprintf(buf, "*/(-)%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(*)/(*)") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "(*)/(*)%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "***") == 0) {
		sort(a, 4);
		sprintf(buf, "***%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*-/") == 0) {
		sprintf(buf, "*-/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(-)*/") == 0) {
		sprintf(buf, "(-)*/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*++") == 0) {
		sort(a, 2);
		sort(&a[2], 2);
		sprintf(buf, "*++%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(-*)*") == 0) {
		sort(&a[1], 2);
		sprintf(buf, "(-*)*%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "**-") == 0) {
		sort(a, 3);
		sprintf(buf, "**-%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*/-") == 0) {
		sort(a, 2);
		sprintf(buf, "*/-%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(+*)*") == 0) {
		sort(&a[1], 2);
		sprintf(buf, "(+*)*%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "+-/") == 0) {
		sort(a, 2);
		sprintf(buf, "+-/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "(+*)/") == 0) {
		sort(&a[1], 2);
		sprintf(buf, "(+*)/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else if (strcmp(formula, "*+/") == 0) {
		sort(a, 2);
		sprintf(buf, "*+/%d%d%d%d", a[0], a[1], a[2], a[3]);
	} else {
		sprintf(buf, "unknown");
		return 0;
	}

	index = exist(buf);
	if (-1 == index) // 已经存在，返回0
		return 0;
	else { // 不存在，加入，返回1
		strcpy(formulas[index], buf);
		return 1;
	}
}

int check(char* formula) {
	// TODO
	return 1;
}

void two_op_two(int x, int y, int u, int v, int total_points) {
	/*
	 x,y 做两两运算: x+y | x-y | y-x | x*y | x/y | y/x
	 u,v 做两两运算: u+v | u-v | v-u | u*v | u/v | v/u
	 对这两个运算结果再做一次运算
	 <+> 表明与别的公式重复
	 <-> 表明不可能得到结果 24

	 ( x+y | x-y | y-x | x*y | x/y | y/x ) + ( u+v | u-v | v-u | u*v | u/v | v/u )
	 x+y+u+v | x+y+u-v <+> | x+y-u+v <+> | x+y+u*v | x+y+u/v | x+y+v/u
	 x-y+u+v | x-y+u-v <+> | x-y-u+v <+> | x-y+u*v | x-y+u/v | x-y+v/u
	 y-x+u+v | y-x+u-v <+> | y-x-u+v <+> | y-x+u*v | y-x+u/v | y-x+v/u
	 x*y+u+v | x*y+u-v <+> | x*y-u+v <+> | x*y+u*v | x*y+u/v | x*y+v/u
	 x/y+u+v | x/y+u-v <+> | x/y-u+v <+> | x/y+u*v | x/y+u/v | x/y+v/u
	 y/x+u+v | y/x+u-v <+> | y/x-u+v <+> | y/x+u*v | y/x+u/v | y/x+v/u */
	if (x + y + u + v == total_points)
		check2("++++", x, y, u, v)
				&& (len += sprintf(result + len, "%d + %d + %d + %d = %d \n", x,
						y, u, v, total_points));
	if (x + y + u * v == total_points)
		check2("*++", u, v, x, y)
				&& (len += sprintf(result + len, "%d + %d + %d * %d = %d \n", x,
						y, u, v, total_points));
	if ((x + y + u / v == total_points) && DIV(u, v))
		check2("/++", u, v, x, y)
				&& (len += sprintf(result + len, "%d + %d + %d / %d = %d \n", x,
						y, u, v, total_points));
	if ((x + y + v / u == total_points) && DIV(v, u))
		check2("/++", v, u, x, y)
				&& (len += sprintf(result + len, "%d + %d + %d / %d = %d \n", x,
						y, v, u, total_points));
	if (x - y + u + v == total_points)
		check2("+++-", x, u, v, y)
				&& (len += sprintf(result + len, "%d - %d + %d + %d = %d \n", x,
						y, u, v, total_points));
	if (x - y + u * v == total_points)
		check2("*+-", v, u, x, y)
				&& (len += sprintf(result + len, "%d * %d + %d - %d = %d \n", u,
						v, x, y, total_points));
	if ((x - y + u / v == total_points) && DIV(u, v))
		check("x-y+u/v")
				&& (len += sprintf(result + len, "%d - %d + %d / %d = %d \n", x,
						y, u, v, total_points));
	if ((x - y + v / u == total_points) && DIV(v, u))
		check("x-y+v/u")
				&& (len += sprintf(result + len, "%d - %d + %d / %d = %d \n", x,
						y, v, u, total_points));
	if (y - x + u + v == total_points)
		check2("+++-", y, u, v, x)
				&& (len += sprintf(result + len, "%d - %d + %d + %d = %d \n", y,
						x, u, v, total_points));
	if (y - x + u * v == total_points)
		check2("*+-", u, v, y, x)
				&& (len += sprintf(result + len, "%d * %d + %d - %d = %d \n", u,
						v, y, x, total_points));
	if ((y - x + u / v == total_points) && DIV(u, v))
		check("y-x+u/v")
				&& (len += sprintf(result + len, "%d - %d + %d / %d = %d \n", y,
						x, u, v, total_points));
	if ((y - x + v / u == total_points) && DIV(v, u))
		check("y-x+v/u")
				&& (len += sprintf(result + len, "%d - %d + %d / %d = %d \n", y,
						x, v, u, total_points));
	if (x * y + u + v == total_points)
		check2("*++", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d + %d + %d = %d \n", x,
						y, u, v, total_points));
	if (x * y + u * v == total_points)
		check2("*+*", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d + %d * %d = %d \n", x,
						y, u, v, total_points));
	if ((x * y + u / v == total_points) && DIV(u, v))
		check2("*+/", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d + %d / %d = %d \n", x,
						y, u, v, total_points));
	if ((x * y + v / u == total_points) && DIV(v, u))
		check2("*+/", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d + %d / %d = %d \n", x,
						y, v, u, total_points));
	if ((x / y + u + v == total_points) && DIV(x, y))
		check2("/++", x, y, u, v)
				&& (len += sprintf(result + len, "%d / %d + %d + %d = %d \n", x,
						y, u, v, total_points));
	if ((x / y + u * v == total_points) && DIV(x, y))
		check2("*+/", u, v, x, y)
				&& (len += sprintf(result + len, "%d / %d + %d * %d = %d \n", x,
						y, u, v, total_points));
	if ((x / y + u / v == total_points) && DIV(x, y) && DIV(u, v))
		check("x/y+u/v")
				&& (len += sprintf(result + len, "%d / %d + %d / %d = %d \n", x,
						y, u, v, total_points));
	if ((x / y + v / u == total_points) && DIV(x, y) && DIV(v, u))
		check("x/y+v/u")
				&& (len += sprintf(result + len, "%d / %d + %d / %d = %d \n", x,
						y, v, u, total_points));
	if ((y / x + u + v == total_points) && DIV(y, x))
		check2("/++", y, x, u, v)
				&& (len += sprintf(result + len, "%d / %d + %d + %d = %d \n", y,
						x, u, v, total_points));
	if ((y / x + u * v == total_points) && DIV(y, x))
		check2("*+/", u, v, y, x)
				&& (len += sprintf(result + len, "%d / %d + %d * %d = %d \n", y,
						x, u, v, total_points));
	if ((y / x + u / v == total_points) && DIV(y, x) && DIV(u, v))
		check("y/x+u/v")
				&& (len += sprintf(result + len, "%d / %d + %d / %d = %d \n", y,
						x, u, v, total_points));
	if ((y / x + v / u == total_points) && DIV(y, x) && DIV(v, u))
		check("y/x+v/u")
				&& (len += sprintf(result + len, "%d / %d + %d / %d = %d \n", y,
						x, v, u, total_points));

	/* ( x+y | x-y | y-x | x*y | x/y | y/x ) - ( u+v | u-v | v-u | u*v | u/v | v/u )
	 x+y-u-v     | x+y-u+v | x+y+u-v | x+y-u*v     | x+y-u/v     | x+y-v/u
	 x-y-u-v <-> | x-y-u+v | x-y+u-v | x-y-u*v <-> | x-y-u/v <-> | x-y-v/u <->
	 y-x-u-v <-> | y-x-u+v | y-x+u-v | y-x-u*v <-> | y-x-u/v <-> | y-x-v/u <->
	 x*y-u-v     | x*y-u+v | x*y+u-v | x*y-u*v     | x*y-u/v     | x*y-v/u
	 x/y-u-v <-> | x/y-u+v | x/y+u-v | x/y-u*v <-> | x/y-u/v <-> | x/y-v/u <->
	 y/x-u-v <-> | y/x-u+v | y/x+u-v | y/x-u*v <-> | y/x-u/v <-> | y/x-v/u <->
	 */
	if (x + y - u - v == total_points)
		check2("++--", x, y, u, v)
				&& (len += sprintf(result + len, "%d + %d - %d - %d = %d \n", x,
						y, u, v, total_points));
	if (x + y - u + v == total_points)
		check2("+++-", x, y, v, u)
				&& (len += sprintf(result + len, "%d + %d - %d + %d = %d \n", x,
						y, u, v, total_points));
	if (x + y + u - v == total_points)
		check2("+++-", x, y, u, v)
				&& (len += sprintf(result + len, "%d + %d + %d - %d = %d \n", x,
						y, u, v, total_points));
	if (x + y - u * v == total_points)
		(len += sprintf(result + len, "%d + %d - %d * %d = %d \n", x, y, u, v,
				total_points));
	if ((x + y - u / v == total_points) && DIV(u, v))
		check2("+-/", x, y, u, v)
				&& (len += sprintf(result + len, "%d + %d - %d / %d = %d \n", x,
						y, u, v, total_points));
	if ((x + y - v / u == total_points) && DIV(v, u))
		check2("+-/", x, y, v, u)
				&& (len += sprintf(result + len, "%d + %d - %d / %d = %d \n", x,
						y, v, u, total_points));
	if (x - y - u + v == total_points)
		check2("++--", x, v, y, u)
				&& (len += sprintf(result + len, "%d - %d - %d + %d = %d \n", x,
						y, u, v, total_points));
	if (x - y + u - v == total_points)
		check2("++--", x, u, y, v)
				&& (len += sprintf(result + len, "%d - %d + %d - %d = %d \n", x,
						y, u, v, total_points));
	if (y - x - u + v == total_points)
		check2("++--", y, v, x, u)
				&& (len += sprintf(result + len, "%d - %d - %d + %d = %d \n", y,
						x, u, v, total_points));
	if (y - x + u - v == total_points)
		check2("++--", y, u, x, v)
				&& (len += sprintf(result + len, "%d - %d + %d - %d = %d \n", y,
						x, u, v, total_points));
	if (x * y - u - v == total_points)
		check2("*--", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d - %d - %d = %d \n", x,
						y, u, v, total_points));
	if (x * y - u + v == total_points)
		check2("*+-", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d + %d - %d = %d \n", x,
						y, v, u, total_points));
	if (x * y + u - v == total_points)
		check2("*+-", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d + %d - %d = %d \n", x,
						y, u, v, total_points));
	if (x * y - u * v == total_points)
		check2("*-*", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d - %d * %d = %d \n", x,
						y, u, v, total_points));
	if ((x * y - u / v == total_points) && DIV(u, v))
		check2("*-/", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d - %d / %d = %d \n", x,
						y, u, v, total_points));
	if ((x * y - v / u == total_points) && DIV(v, u))
		check2("*-/", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d - %d / %d = %d \n", x,
						y, v, u, total_points));
	if ((x / y - u + v == total_points) && DIV(x, y))
		(len += sprintf(result + len, "%d / %d - %d + %d = %d \n", x, y, u, v,
				total_points));
	if ((x / y + u - v == total_points) && DIV(x, y))
		(len += sprintf(result + len, "%d / %d + %d - %d = %d \n", x, y, u, v,
				total_points));
	if ((y / x - u + v == total_points) && DIV(y, x))
		(len += sprintf(result + len, "%d / %d - %d + %d = %d \n", y, x, u, v,
				total_points));
	if ((y / x + u - v == total_points) && DIV(y, x))
		(len += sprintf(result + len, "%d / %d + %d - %d = %d \n", y, x, u, v,
				total_points));

	/* ( u+v | u-v | v-u | u*v | u/v | v/u ) - ( x+y | x-y | y-x | x*y | x/y | y/x )
	 u+v-x-y     | u+v-x+y | u+v+x-y | u+v-x*y     | u+v-x/y     | u+v-y/x
	 u-v-x-y <-> | u-v-x+y | u-v+x-y | u-v-x*y <-> | u-v-x/y <-> | u-v-y/x <->
	 v-u-x-y <-> | v-u-x+y | v-u+x-y | v-u-x*y <-> | v-u-x/y <-> | v-u-y/x <->
	 u*v-x-y     | u*v-x+y | u*v+x-y | u*v-x*y     | u*v-x/y     | u*v-y/x
	 u/v-x-y <-> | u/v-x+y | u/v+x-y | u/v-x*y <-> | u/v-x/y <-> | u/v-y/x <->
	 v/u-x-y <-> | v/u-x+y | v/u+x-y | v/u-x*y <-> | v/u-x/y <-> | v/u-y/x <->
	 */
	if (u + v - x - y == total_points)
		check2("++--", u, v, x, y)
				&& (len += sprintf(result + len, "%d + %d - %d - %d = %d \n", u,
						v, x, y, total_points));
	if (u + v - x + y == total_points)
		check2("+++-", u, v, y, x)
				&& (len += sprintf(result + len, "%d + %d - %d + %d = %d \n", u,
						v, x, y, total_points));
	if (u + v + x - y == total_points)
		check2("+++-", u, v, x, y)
				&& (len += sprintf(result + len, "%d + %d + %d - %d = %d \n", u,
						v, x, y, total_points));
	if (u + v - x * y == total_points)
		(len += sprintf(result + len, "%d + %d - %d * %d = %d \n", u, v, x, y,
				total_points));
	if ((u + v - x / y == total_points) && DIV(x, y))
		(len += sprintf(result + len, "%d + %d - %d / %d = %d \n", u, v, x, y,
				total_points));
	if ((u + v - y / x == total_points) && DIV(y, x))
		(len += sprintf(result + len, "%d + %d - %d / %d = %d \n", u, v, y, x,
				total_points));
	if (u - v - x + y == total_points)
		check2("++--", u, y, v, x)
				&& (len += sprintf(result + len, "%d - %d - %d + %d = %d \n", u,
						v, x, y, total_points));
	if (u - v + x - y == total_points)
		check2("++--", u, x, v, y)
				&& (len += sprintf(result + len, "%d - %d + %d - %d = %d \n", u,
						v, x, y, total_points));
	if (v - u - x + y == total_points)
		check2("++--", v, y, u, x)
				&& (len += sprintf(result + len, "%d - %d - %d + %d = %d \n", v,
						u, x, y, total_points));
	if (v - u + x - y == total_points)
		check2("++--", v, x, u, y)
				&& (len += sprintf(result + len, "%d - %d + %d - %d = %d \n", v,
						u, x, y, total_points));
	if (u * v - x - y == total_points)
		check2("*--", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d - %d - %d = %d \n", u,
						v, x, y, total_points));
	if (u * v - x + y == total_points)
		check2("*+-", u, v, y, x)
				&& (len += sprintf(result + len, "%d * %d - %d + %d = %d \n", u,
						v, x, y, total_points));
	if (u * v + x - y == total_points)
		check2("*+-", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d + %d - %d = %d \n", u,
						v, x, y, total_points));
	if (u * v - x * y == total_points)
		check2("*-*", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d - %d * %d = %d \n", u,
						v, x, y, total_points));
	if ((u * v - x / y == total_points) && DIV(x, y))
		check2("*-/", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d - %d / %d = %d \n", u,
						v, x, y, total_points));
	if ((u * v - y / x == total_points) && DIV(y, x))
		check2("*-/", u, v, y, x)
				&& (len += sprintf(result + len, "%d * %d - %d / %d = %d \n", u,
						v, y, x, total_points));
	if ((u / v - x + y == total_points) && DIV(u, v))
		(len += sprintf(result + len, "%d / %d - %d + %d = %d \n", u, v, x, y,
				total_points));
	if ((u / v + x - y == total_points) && DIV(u, v))
		(len += sprintf(result + len, "%d / %d + %d - %d = %d \n", u, v, x, y,
				total_points));
	if ((v / u - x + y == total_points) && DIV(v, u))
		(len += sprintf(result + len, "%d / %d - %d + %d = %d \n", v, u, x, y,
				total_points));
	if ((v / u + x - y == total_points) && DIV(v, u))
		(len += sprintf(result + len, "%d / %d + %d - %d = %d \n", v, u, x, y,
				total_points));

	/* ( x+y | x-y | y-x | x*y | x/y | y/x ) * ( u+v | u-v | v-u | u*v | u/v | v/u )
	 (x+y)*(u+v) | (x+y)*(u-v)     | (x+y)*(v-u) | (x+y)*u*v | (x+y)*u/v <+> | (x+y)*v/u <+>
	 (x-y)*(u+v) | (x-y)*(u-v) <+> | (x-y)*(v-u) | (x-y)*u*v | (x-y)*u/v <+> | (x-y)*v/u <+>
	 (y-x)*(u+v) | (y-x)*(u-v) <+> | (y-x)*(v-u) | (y-x)*u*v | (y-x)*u/v <+> | (y-x)*v/u <+>
	 (x*y)*(u+v) | (x*y)*(u-v)     | (x*y)*(v-u) | (x*y)*u*v | (x*y)*u/v <+> | (x*y)*v/u <+>
	 (x/y)*(u+v) | (x/y)*(u-v)     | (x/y)*(v-u) | (x/y)*u*v | (x/y)*u/v <+> | (x/y)*v/u <+>
	 (y/x)*(u+v) | (y/x)*(u-v)     | (y/x)*(v-u) | (y/x)*u*v | (y/x)*u/v <+> | (y/x)*v/u <+> */
	if ((x + y) * (u + v) == total_points)
		check2("(+)*(+)", x, y, u, v)
				&& (len += sprintf(result + len,
						"(%d + %d) * (%d + %d) = %d \n", x, y, u, v,
						total_points));
	if ((x + y) * (u - v) == total_points)
		check2("(+)*(-)", x, y, u, v)
				&& (len += sprintf(result + len,
						"(%d + %d) * (%d - %d) = %d \n", x, y, u, v,
						total_points));
	if ((x + y) * (v - u) == total_points)
		check2("(+)*(-)", x, y, v, u)
				&& (len += sprintf(result + len,
						"(%d + %d) * (%d - %d) = %d \n", x, y, v, u,
						total_points));
	if ((x + y) * u * v == total_points)
		(len += sprintf(result + len, "(%d + %d) * %d * %d = %d \n", x, y, u, v,
				total_points));
	if ((x - y) * (u + v) == total_points)
		check2("(+)*(-)", u, v, x, y)
				&& (len += sprintf(result + len,
						"(%d - %d) * (%d + %d) = %d \n", x, y, u, v,
						total_points));
	if ((x - y) * (v - u) == total_points)
		check2("(-)*(-)", x, y, v, u)
				&& (len += sprintf(result + len,
						"(%d - %d) * (%d - %d) = %d \n", x, y, v, u,
						total_points));
	if ((x - y) * u * v == total_points)
		check2("(-)**", x, y, u, v)
				&& (len += sprintf(result + len, "(%d - %d) * %d * %d = %d \n",
						x, y, u, v, total_points));
	if ((y - x) * (u + v) == total_points)
		check2("(+)*(-)", u, v, y, x)
				&& (len += sprintf(result + len,
						"(%d - %d) * (%d + %d) = %d \n", y, x, u, v,
						total_points));
	if ((y - x) * (v - u) == total_points)
		check2("(-)*(-)", x, y, u, v)
				&& (len += sprintf(result + len,
						"(%d - %d) * (%d - %d) = %d \n", y, x, v, u,
						total_points));
	if ((y - x) * u * v == total_points)
		check2("(-)**", y, x, u, v)
				&& (len += sprintf(result + len, "(%d - %d) * %d * %d = %d \n",
						y, x, u, v, total_points));
	if ((x * y) * (u + v) == total_points)
		(len += sprintf(result + len, "(%d * %d) * (%d + %d) = %d \n", x, y, u,
				v, total_points));
	if ((x * y) * (u - v) == total_points)
		check2("(-)**", u, v, x, y)
				&& (len += sprintf(result + len,
						"(%d * %d) * (%d - %d) = %d \n", x, y, u, v,
						total_points));
	if ((x * y) * (v - u) == total_points)
		check2("(-)**", v, u, x, y)
				&& (len += sprintf(result + len,
						"(%d * %d) * (%d - %d) = %d \n", x, y, v, u,
						total_points));
	if ((x * y) * u * v == total_points)
		check2("***", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d * %d * %d = %d \n", x,
						y, u, v, total_points));
	if (((x / y) * (u + v) == total_points) && DIV(x, y))
		check2("(+)*/", v, u, x, y)
				&& (len += sprintf(result + len, "(%d + %d) * %d / %d = %d \n",
						u, v, x, y, total_points));
	if (((x / y) * (u - v) == total_points) && DIV(x, y))
		check2("(-)*/", u, v, x, y)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						u, v, x, y, total_points));
	if (((x / y) * (v - u) == total_points) && DIV(x, y))
		check2("(-)*/", v, u, x, y)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						v, u, x, y, total_points));
	// if (((x/y)*u*v  ==24) 被 **/代替
	if (((y / x) * (u + v) == total_points) && DIV(y, x))
		check2("(+)*/", v, u, y, x)
				&& (len += sprintf(result + len, "(%d + %d) * %d / %d = %d \n",
						u, v, y, x, total_points));
	if (((y / x) * (u - v) == total_points) && DIV(y, x))
		check2("(-)*/", u, v, y, x)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						u, v, y, x, total_points));
	if (((y / x) * (v - u) == total_points) && DIV(y, x))
		check2("(-)*/", v, u, y, x)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						v, u, y, x, total_points));
	// if (((y/x)*u*v  ==24) 被 **/代替

	/* ( x+y | x-y | y-x | x*y | x/y | y/x ) / ( u+v | u-v | v-u | u*v | u/v | v/u )
	 (x+y)/(u+v) <-> | (x+y)/(u-v)     | (x+y)/(v-u)     | (x+y)/(u*v)     | (x+y)*v/u | (x+y)*u/v
	 (x-y)/(u+v) <-> | (x-y)/(u-v) <-> | (x-y)/(v-u) <-> | (x-y)/(u*v) <-> | (x-y)*v/u | (x-y)*u/v
	 (y-x)/(u+v) <-> | (y-x)/(u-v) <-> | (y-x)/(v-u) <-> | (y-x)/(u*v) <-> | (y-x)*v/u | (y-x)*u/v
	 (x*y)/(u+v)     | (x*y)/(u-v)     | (x*y)/(v-u)     | (x*y)/(u*v)     | (x*y)*v/u | (x*y)*u/v
	 (x/y)/(u+v) <-> | (x/y)/(u-v) <-> | (x/y)/(v-u) <-> | (x/y)/(u*v) <-> | (x/y)*v/u | (x/y)*u/v
	 (y/x)/(u+v) <-> | (y/x)/(u-v) <-> | (y/x)/(v-u) <-> | (y/x)/(u*v) <-> | (y/x)*v/u | (y/x)*u/v */
	if ((u != v) && ((x + y) / (u - v) == total_points) && DIV(x + y, u - v))
		(len += sprintf(result + len, "(%d + %d) / (%d - %d) = %d \n", x, y, u,
				v, total_points));
	if ((u != v) && ((x + y) / (v - u) == total_points) && DIV(x + y, v - u))
		(len += sprintf(result + len, "(%d + %d) / (%d - %d) = %d \n", x, y, v,
				u, total_points));
	if (((x + y) / (u * v) == total_points) && DIV(x + y, u * v))
		(len += sprintf(result + len, "(%d + %d) / (%d * %d) = %d \n", x, y, u,
				v, total_points));
	if (((x + y) * v / u == total_points) && DIV((x + y) * v, u))
		check2("(+)*/", x, y, v, u)
				&& (len += sprintf(result + len, "(%d + %d) * %d / %d = %d \n",
						x, y, v, u, total_points));
	if (((x + y) * u / v == total_points) && DIV((x + y) * u, v))
		check2("(+)*/", x, y, u, v)
				&& (len += sprintf(result + len, "(%d + %d) * %d / %d = %d \n",
						x, y, u, v, total_points));
	if (((x - y) * v / u == total_points) && DIV((x - y) * v, u))
		check2("(-)*/", x, y, v, u)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						x, y, v, u, total_points));
	if (((x - y) * u / v == total_points) && DIV((x - y) * u, v))
		check2("(-)*/", x, y, u, v)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						x, y, u, v, total_points));
	if (((y - x) * v / u == total_points) && DIV((y - x) * v, u))
		check2("(-)*/", y, x, v, u)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						y, x, v, u, total_points));
	if (((y - x) * u / v == total_points) && DIV((y - x) * u, v))
		check2("(-)*/", y, x, u, v)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						y, x, u, v, total_points));
	if (((x * y) / (u + v) == total_points) && DIV(x * y, u + v))
		(len += sprintf(result + len, "%d * %d / (%d + %d) = %d \n", x, y, u, v,
				total_points));
	if ((u != v) && ((x * y) / (u - v) == total_points) && DIV(x * y, u - v))
		check2("*/(-)", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d / (%d - %d) = %d \n",
						x, y, u, v, total_points));
	if ((u != v) && ((x * y) / (v - u) == total_points) && DIV(x * y, v - u))
		check2("*/(-)", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d / (%d - %d) = %d \n",
						x, y, v, u, total_points));
	if (((x * y) / (u * v) == total_points) && DIV(x * y, u * v))
		check2("(*)/(*)", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d / (%d * %d) = %d \n",
						x, y, u, v, total_points));
	if (((x * y) * v / u == total_points) && DIV(x * y * v, u))
		check2("**/", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d * %d / %d = %d \n", x,
						y, v, u, total_points));
	if (((x * y) * u / v == total_points) && DIV(x * y * u, v))
		check2("**/", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d * %d / %d = %d \n", x,
						y, u, v, total_points));
	if (((x * v) / (y * u) == total_points) && DIV(x * v, y * u))
		check2("(*)/(*)", x, v, y, u)
				&& (len += sprintf(result + len, "%d * %d / (%d * %d) = %d \n",
						x, v, y, u, total_points));
	if (((x * u) / (y * v) == total_points) && DIV(x * u, y * v))
		check2("(*)/(*)", x, u, y, v)
				&& (len += sprintf(result + len, "%d * %d / (%d * %d) = %d \n",
						x, u, y, v, total_points));
	if (((y * v) / (x * u) == total_points) && DIV(y * v, x * u))
		check2("(*)/(*)", y, v, x, u)
				&& (len += sprintf(result + len, "%d * %d / (%d * %d) = %d \n",
						y, v, x, u, total_points));
	if (((y * u) / (x * v) == total_points) && DIV(y * u, x * v))
		check2("(*)/(*)", y, u, x, v)
				&& (len += sprintf(result + len, "%d * %d / (%d * %d) = %d \n",
						y, u, x, v, total_points));

	/* ( u+v | u-v | v-u | u*v | u/v | v/u ) / ( x+y | x-y | y-x | x*y | x/y | y/x )
	 (u+v)/(x+y) <-> | (u+v)/(x-y)     | (u+v)/(y-x)     | (u+v)/(x*y)     | (u+v)/(x/y) | (u+v)/(y/x)
	 (u-v)/(x+y) <-> | (u-v)/(x-y) <-> | (u-v)/(y-x) <-> | (u-v)/(x*y) <-> | (u-v)/(x/y) | (u-v)/(y/x)
	 (v-u)/(x+y) <-> | (v-u)/(x-y) <-> | (v-u)/(y-x) <-> | (v-u)/(x*y) <-> | (v-u)/(x/y) | (v-u)/(y/x)
	 (u*v)/(x+y)     | (u*v)/(x-y)     | (u*v)/(y-x)     | (u*v)/(x*y)     | (u*v)/(x/y) | (u*v)/(y/x)
	 (u/v)/(x+y) <-> | (u/v)/(x-y) <-> | (u/v)/(y-x) <-> | (u/v)/(x*y) <-> | (u/v)/(x/y) | (u/v)/(y/x)
	 (v/u)/(x+y) <-> | (v/u)/(x-y) <-> | (v/u)/(y-x) <-> | (v/u)/(x*y) <-> | (v/u)/(x/y) | (v/u)/(y/x) */
	if ((x != y) && ((u + v) / (x - y) == total_points) && DIV(u + v, x - y))
		(len += sprintf(result + len, "(%d + %d) / (%d - %d) = %d \n", u, v, x,
				y, total_points));
	if ((x != y) && ((u + v) / (y - x) == total_points) && DIV(u + v, y - x))
		(len += sprintf(result + len, "(%d + %d) / (%d - %d) = %d \n", u, v, y,
				x, total_points));
	if (((u + v) / (x * y) == total_points) && DIV(u + v, x * y))
		(len += sprintf(result + len, "(%d + %d) / (%d * %d) = %d \n", u, v, x,
				y, total_points));
	if (((u + v) * y / x == total_points) && DIV((u + v) * y, x))
		check2("(+)*/", u, v, y, x)
				&& (len += sprintf(result + len, "(%d + %d) * %d / %d = %d \n",
						u, v, y, x, total_points));
	if (((u + v) * x / y == total_points) && DIV((u + v) * x, y))
		check2("(+)*/", u, v, x, y)
				&& (len += sprintf(result + len, "(%d + %d) * %d / %d = %d \n",
						u, v, x, y, total_points));
	if (((u - v) * y / x == total_points) && DIV((u - v) * y, x))
		check2("(-)*/", u, v, y, x)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						u, v, y, x, total_points));
	if (((u - v) * x / y == total_points) && DIV((u - v) * x, y))
		check2("(-)*/", u, v, x, y)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						u, v, x, y, total_points));
	if (((v - u) * y / x == total_points) && DIV((v - u) * y, x))
		check2("(-)*/", v, u, y, x)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						v, u, y, x, total_points));
	if (((v - u) * x / y == total_points) && DIV((v - u) * x, y))
		check2("(-)*/", v, u, x, y)
				&& (len += sprintf(result + len, "(%d - %d) * %d / %d = %d \n",
						v, u, x, y, total_points));
	if (((u * v) / (x + y) == total_points) && DIV(u * v, x + y))
		(len += sprintf(result + len, "%d * %d / (%d + %d) = %d \n", u, v, x, y,
				total_points));
	if ((x != y) && ((u * v) / (x - y) == total_points) && DIV(u * v, x - y))
		check2("*/(-)", v, u, x, y)
				&& (len += sprintf(result + len, "%d * %d / (%d - %d) = %d \n",
						u, v, x, y, total_points));
	if ((x != y) && ((u * v) / (y - x) == total_points) && DIV(u * v, y - x))
		check2("*/(-)", v, u, y, x)
				&& (len += sprintf(result + len, "%d * %d / (%d - %d) = %d \n",
						u, v, y, x, total_points));
	if (((u * v) / (x * y) == total_points) && DIV(u * v, x * y))
		check2("(*)/(*)", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d / (%d * %d) = %d \n",
						u, v, x, y, total_points));
	if (((u * v) * y / x == total_points) && DIV(u * v * y, x))
		check2("**/", u, v, y, x)
				&& (len += sprintf(result + len, "%d * %d * %d / %d = %d \n", u,
						v, y, x, total_points));
	if (((u * v) * x / y == total_points) && DIV(u * v * x, y))
		check2("**/", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d * %d / %d = %d \n", u,
						v, x, y, total_points));
	if (((u * y) / (v * x) == total_points) && DIV(u * y, v * x))
		check2("(*)/(*)", u, y, v, x)
				&& (len += sprintf(result + len, "(%d * %d / (%d * %d) = %d \n",
						u, y, v, x, total_points));
	if (((u * x) / (v * y) == total_points) && DIV(u * x, v * y))
		check2("(*)/(*)", u, x, v, y)
				&& (len += sprintf(result + len, "(%d * %d / (%d * %d) = %d \n",
						u, x, v, y, total_points));
	if (((v * y) / (u * x) == total_points) && DIV(v * y, u * x))
		check2("(*)/(*)", v, y, u, x)
				&& (len += sprintf(result + len, "(%d * %d / (%d * %d) = %d \n",
						v, y, u, x, total_points));
	if (((v * x) / (u * y) == total_points) && DIV(v * x, u * y))
		check2("(*)/(*)", v, x, u, y)
				&& (len += sprintf(result + len, "(%d * %d / (%d * %d) = %d \n",
						v, x, u, y, total_points));

}

void triple_op(int x, int y, int u, int v, int total_points) {
	/*
	 * 先得到三个参数的运算结果，然后和第四个参数进行运算，有以下几种可能
	 * (x+y*u)*v (y+u*v)*x (u+v*x)*y (v+x*y)*u
	 * (y+u*x)*v (u+y*v)*x (v+x*u)*y (x+y*v)*u
	 * (u+x*y)*v (y+v*u)*x (x+u*v)*y (y+v*x)*u
	 * (x-y*u)*v (y-u*v)*x (u-v*x)*y (v-x*y)*u
	 * (y-u*x)*v (u-y*v)*x (v-x*u)*y (x-y*v)*u
	 * (u-x*y)*v (y-v*u)*x (x-u*v)*y (y-v*x)*u
	 * (x*y-u)*v (y*u-v)*x (u*v-x)*y (v*x-y)*u
	 * (y*u-x)*v (u*y-v)*x (v*x-u)*y (x*y-v)*u
	 * (u*x-y)*v (y*v-u)*x (x*u-v)*y (y*v-x)*u */
	if ((x + y * u) * v == total_points)
		check2("(+*)*", x, y, u, v)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						x, y, u, v, total_points));
	if ((y + u * v) * x == total_points)
		check2("(+*)*", y, u, v, x)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						y, u, v, x, total_points));
	if ((u + v * x) * y == total_points)
		check2("(+*)*", u, v, x, y)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						u, v, x, y, total_points));
	if ((v + x * y) * u == total_points)
		check2("(+*)*", v, x, y, u)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						v, x, y, u, total_points));
	if ((y + u * x) * v == total_points)
		check2("(+*)*", y, u, x, v)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						y, u, x, v, total_points));
	if ((u + y * v) * x == total_points)
		check2("(+*)*", u, y, v, x)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						u, y, v, x, total_points));
	if ((v + x * u) * y == total_points)
		check2("(+*)*", v, x, u, y)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						v, x, u, y, total_points));
	if ((x + y * v) * u == total_points)
		check2("(+*)*", x, y, v, u)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						x, y, v, u, total_points));
	if ((u + x * y) * v == total_points)
		check2("(+*)*", u, x, y, v)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						u, x, y, v, total_points));
	if ((y + v * u) * x == total_points)
		check2("(+*)*", y, v, u, x)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						y, v, u, x, total_points));
	if ((x + u * v) * y == total_points)
		check2("(+*)*", x, u, v, y)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						x, u, v, y, total_points));
	if ((y + v * x) * u == total_points)
		check2("(+*)*", y, v, x, u)
				&& (len += sprintf(result + len, "(%d + %d * %d) * %d = %d \n",
						y, v, x, u, total_points));
	if ((x - y * u) * v == total_points)
		check2("(-*)*", x, y, u, v)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						x, y, u, v, total_points));
	if ((y - u * v) * x == total_points)
		check2("(-*)*", y, u, v, x)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						y, u, v, x, total_points));
	if ((u - v * x) * y == total_points)
		check2("(-*)*", u, v, x, y)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						u, v, x, y, total_points));
	if ((v - x * y) * u == total_points)
		check2("(-*)*", v, x, y, u)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						v, x, y, u, total_points));
	if ((y - u * x) * v == total_points)
		check2("(-*)*", y, u, x, v)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						y, u, x, v, total_points));
	if ((u - y * v) * x == total_points)
		check2("(-*)*", u, y, v, x)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						u, y, v, x, total_points));
	if ((v - x * u) * y == total_points)
		check2("(-*)*", v, x, u, y)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						v, x, u, y, total_points));
	if ((x - y * v) * u == total_points)
		check2("(-*)*", x, y, v, u)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						x, y, v, u, total_points));
	if ((u - x * y) * v == total_points)
		check2("(-*)*", u, x, y, v)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						u, x, y, v, total_points));
	if ((y - v * u) * x == total_points)
		check2("(-*)*", y, v, u, x)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						y, v, u, x, total_points));
	if ((x - u * v) * y == total_points)
		check2("(-*)*", x, u, v, y)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						x, u, v, y, total_points));
	if ((y - v * x) * u == total_points)
		check2("(-*)*", y, v, x, u)
				&& (len += sprintf(result + len, "(%d - %d * %d) * %d = %d \n",
						y, v, x, u, total_points));
	if ((x * y - u) * v == total_points)
		check2("(*-)*", x, y, u, v)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						x, y, u, v, total_points));
	if ((y * u - v) * x == total_points)
		check2("(*-)*", y, u, v, x)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						y, u, v, x, total_points));
	if ((u * v - x) * y == total_points)
		check2("(*-)*", u, v, x, y)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						u, v, x, y, total_points));
	if ((v * x - y) * u == total_points)
		check2("(*-)*", v, x, y, u)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						v, x, y, u, total_points));
	if ((y * u - x) * v == total_points)
		check2("(*-)*", y, u, x, v)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						y, u, x, v, total_points));
	if ((u * y - v) * x == total_points)
		check2("(*-)*", u, y, v, x)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						u, y, v, x, total_points));
	if ((v * x - u) * y == total_points)
		check2("(*-)*", v, x, u, y)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						v, x, u, y, total_points));
	if ((x * y - v) * u == total_points)
		check2("(*-)*", x, y, v, u)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						x, y, v, u, total_points));
	if ((u * x - y) * v == total_points)
		check2("(*-)*", u, x, y, v)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						u, x, y, v, total_points));
	if ((y * v - u) * x == total_points)
		check2("(*-)*", y, v, u, x)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						y, v, u, x, total_points));
	if ((x * u - v) * y == total_points)
		check2("(*-)*", x, u, v, y)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						x, u, v, y, total_points));
	if ((y * v - x) * u == total_points)
		check2("(*-)*", y, v, x, u)
				&& (len += sprintf(result + len, "(%d * %d - %d) * %d = %d \n",
						y, v, x, u, total_points));

	/*
	 * (x+y*u)/v (y+u*v)/x (u+v*x)/y (v+x*y)/u
	 * (y+u*x)/v (u+y*v)/x (v+x*u)/y (x+y*v)/u
	 * (u+x*y)/v (y+v*u)/x (x+u*v)/y (y+v*x)/u
	 * (x*y-u)/v (y*u-v)/x (u*v-x)/y (v*x-y)/u
	 * (y*u-x)/v (u*y-v)/x (v*x-u)/y (x*y-v)/u
	 * (u*x-y)/v (y*v-u)/x (x*u-v)/y (y*v-x)/u
	 * (x+y+u)*v (y+u+v)*x (u+v+x)*y (v+x+y)*u
	 * (x+y-u)*v (y+u-v)*x (u+v-x)*y (v+x-y)*u
	 * (x+u-y)*v (y+v-u)*x (u+x-v)*y (v+y-x)*u
	 * (y+u-x)*v (u+v-y)*x (x+v-u)*y (x+y-v)*u
	 * (x-y-u)*v (y-u-v)*x (x-u-v)*y (v-x-y)*u
	 * (y-u-x)*v (u-v-y)*x (u-v-x)*y (x-y-v)*u
	 * (u-x-y)*v (v-y-u)*x (v-x-u)*y (y-v-x)*u
	 * (x+y+u)/v (y+u+v)/x (u+v+x)/y (v+x+y)/u
	 * (x+y-u)/v (y+u-v)/x (u+v-x)/y (v+x-y)/u
	 * (x-y+u)/v (y-u+v)/x (u-v+x)/y (v-x+y)/u */
	if (((x + y * u) / v == total_points) && DIV(x + y * u, v))
		check2("(+*)/", x, y, u, v)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						x, y, u, v, total_points));
	if (((y + u * v) / x == total_points) && DIV(y + u * v, x))
		check2("(+*)/", y, u, v, x)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						y, u, v, x, total_points));
	if (((u + v * x) / y == total_points) && DIV(u + v * x, y))
		check2("(+*)/", u, v, x, y)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						u, v, x, y, total_points));
	if (((v + x * y) / u == total_points) && DIV(v + x * y, u))
		check2("(+*)/", v, x, y, u)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						v, x, y, u, total_points));
	if (((y + u * x) / v == total_points) && DIV(y + u * x, v))
		check2("(+*)/", y, u, x, v)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						y, u, x, v, total_points));
	if (((u + y * v) / x == total_points) && DIV(u + y * v, x))
		check2("(+*)/", u, y, v, x)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						u, y, v, x, total_points));
	if (((v + x * u) / y == total_points) && DIV(v + x * u, y))
		check2("(+*)/", v, x, u, y)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						v, x, u, y, total_points));
	if (((x + y * v) / u == total_points) && DIV(x + y * v, u))
		check2("(+*)/", x, y, v, u)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						x, y, v, u, total_points));
	if (((u + x * y) / v == total_points) && DIV(u + x * y, v))
		check2("(+*)/", u, x, y, v)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						u, x, y, v, total_points));
	if (((y + v * u) / x == total_points) && DIV(y + v * u, x))
		check2("(+*)/", y, v, u, x)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						y, v, u, x, total_points));
	if (((x + u * v) / y == total_points) && DIV(x + u * v, y))
		check2("(+*)/", x, u, v, y)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						x, u, v, y, total_points));
	if (((y + v * x) / u == total_points) && DIV(y + v * x, u))
		check2("(+*)/", y, v, x, u)
				&& (len += sprintf(result + len, "(%d + %d * %d) / %d = %d \n",
						y, v, x, u, total_points));
	if (((x * y - u) / v == total_points) && DIV(x * y - u, v))
		check2("(*-)/", x, y, u, v)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						x, y, u, v, total_points));
	if (((y * u - v) / x == total_points) && DIV(y * u - v, x))
		check2("(*-)/", y, u, v, x)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						y, u, v, x, total_points));
	if (((u * v - x) / y == total_points) && DIV(u * v - x, y))
		check2("(*-)/", u, v, x, y)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						u, v, x, y, total_points));
	if (((v * x - y) / u == total_points) && DIV(v * x - y, u))
		check2("(*-)/", v, x, y, u)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						v, x, y, u, total_points));
	if (((y * u - x) / v == total_points) && DIV(y * u - x, v))
		check2("(*-)/", y, u, x, v)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						y, u, x, v, total_points));
	if (((u * y - v) / x == total_points) && DIV(u * y - v, x))
		check2("(*-)/", u, y, v, x)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						u, y, v, x, total_points));
	if (((v * x - u) / y == total_points) && DIV(v * x - u, y))
		check2("(*-)/", v, x, u, y)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						v, x, u, y, total_points));
	if (((x * y - v) / u == total_points) && DIV(x * y - v, u))
		check2("(*-)/", x, y, v, u)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						x, y, v, u, total_points));
	if (((u * x - y) / v == total_points) && DIV(u * x - y, v))
		check2("(*-)/", u, x, y, v)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						u, x, y, v, total_points));
	if (((y * v - u) / x == total_points) && DIV(y * v - u, x))
		check2("(*-)/", y, v, u, x)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						y, v, u, x, total_points));
	if (((x * u - v) / y == total_points) && DIV(x * u - v, y))
		check2("(*-)/", x, u, v, y)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						x, u, v, y, total_points));
	if (((y * v - x) / u == total_points) && DIV(y * v - x, u))
		check2("(*-)/", y, v, x, u)
				&& (len += sprintf(result + len, "(%d * %d - %d) / %d = %d \n",
						y, v, x, u, total_points));
	if (((x + y + u) * v == total_points))
		check2("(++)*", x, y, u, v)
				&& (len += sprintf(result + len, "(%d + %d + %d) * %d = %d \n",
						x, y, u, v, total_points));
	if (((y + u + v) * x == total_points))
		check2("(++)*", y, u, v, x)
				&& (len += sprintf(result + len, "(%d + %d + %d) * %d = %d \n",
						y, u, v, x, total_points));
	if (((u + v + x) * y == total_points))
		check2("(++)*", u, v, x, y)
				&& (len += sprintf(result + len, "(%d + %d + %d) * %d = %d \n",
						u, v, x, y, total_points));
	if (((v + x + y) * u == total_points))
		check2("(++)*", v, x, y, u)
				&& (len += sprintf(result + len, "(%d + %d + %d) * %d = %d \n",
						v, x, y, u, total_points));

	if (((x + y - u) * v == total_points))
		check2("(+-)*", x, y, u, v)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						x, y, u, v, total_points));
	if (((y + u - v) * x == total_points))
		check2("(+-)*", y, u, v, x)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						y, u, v, x, total_points));
	if (((u + v - x) * y == total_points))
		check2("(+-)*", u, v, x, y)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						u, v, x, y, total_points));
	if (((v + x - y) * u == total_points))
		check2("(+-)*", v, x, y, u)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						v, x, y, u, total_points));
	if (((x + u - y) * v == total_points))
		check2("(+-)*", x, u, y, v)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						x, u, y, v, total_points));
	if (((y + v - u) * x == total_points))
		check2("(+-)*", y, v, u, x)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						y, v, u, x, total_points));
	if (((u + x - v) * y == total_points))
		check2("(+-)*", u, x, v, y)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						u, x, v, y, total_points));
	if (((v + y - x) * u == total_points))
		check2("(+-)*", v, y, x, u)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						v, y, x, u, total_points));
	if (((y + u - x) * v == total_points))
		check2("(+-)*", y, u, x, v)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						y, u, x, v, total_points));
	if (((u + v - y) * x == total_points))
		check2("(+-)*", u, v, y, x)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						u, v, y, x, total_points));
	if (((x + v - u) * y == total_points))
		check2("(+-)*", x, v, u, y)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						x, v, u, y, total_points));
	if (((x + y - v) * u == total_points))
		check2("(+-)*", x, y, v, u)
				&& (len += sprintf(result + len, "(%d + %d - %d) * %d = %d \n",
						x, y, v, u, total_points));

	if (((x - y - u) * v == total_points))
		(len += sprintf(result + len, "(%d - %d - %d) * %d = %d \n", x, y, u, v,
				total_points));
	if (((y - u - v) * x == total_points))
		(len += sprintf(result + len, "(%d - %d - %d) * %d = %d \n", y, u, v, x,
				total_points));
	if (((u - v - x) * y == total_points))
		(len += sprintf(result + len, "(%d - %d - %d) * %d = %d \n", u, v, x, y,
				total_points));
	if (((v - x - y) * u == total_points))
		(len += sprintf(result + len, "(%d - %d - %d) * %d = %d \n", v, x, y, u,
				total_points));
	if (((x + y + u) / v == total_points) && DIV(x + y + u, v))
		(len += sprintf(result + len, "(%d + %d + %d) / %d = %d \n", x, y, u, v,
				total_points));
	if (((y + u + v) / x == total_points) && DIV(y + u + v, x))
		(len += sprintf(result + len, "(%d + %d + %d) / %d = %d \n", y, u, v, x,
				total_points));
	if (((u + v + x) / y == total_points) && DIV(u + v + x, y))
		(len += sprintf(result + len, "(%d + %d + %d) / %d = %d \n", u, v, x, y,
				total_points));
	if (((v + x + y) / u == total_points) && DIV(v + x + y, u))
		(len += sprintf(result + len, "(%d + %d + %d) / %d = %d \n", v, x, y, u,
				total_points));
	if (((x + y - u) / v == total_points) && DIV(x + y - u, v))
		(len += sprintf(result + len, "(%d + %d - %d) / %d = %d \n", x, y, u, v,
				total_points));
	if (((y + u - v) / x == total_points) && DIV(y + u - v, x))
		(len += sprintf(result + len, "(%d + %d - %d) / %d = %d \n", y, u, v, x,
				total_points));
	if (((u + v - x) / y == total_points) && DIV(u + v - x, y))
		(len += sprintf(result + len, "(%d + %d - %d) / %d = %d \n", u, v, x, y,
				total_points));
	if (((v + x - y) / u == total_points) && DIV(v + x - y, u))
		(len += sprintf(result + len, "(%d + %d - %d) / %d = %d \n", v, x, y, u,
				total_points));
	if (((x - y + u) / v == total_points) && DIV(x - y + u, v))
		(len += sprintf(result + len, "(%d - %d + %d) / %d = %d \n", x, y, u, v,
				total_points));
	if (((y - u + v) / x == total_points) && DIV(y - u + v, x))
		(len += sprintf(result + len, "(%d - %d + %d) / %d = %d \n", y, u, v, x,
				total_points));
	if (((u - v + x) / y == total_points) && DIV(u - v + x, y))
		(len += sprintf(result + len, "(%d - %d + %d) / %d = %d \n", u, v, x, y,
				total_points));
	if (((v - x + y) / u == total_points) && DIV(v - x + y, u))
		(len += sprintf(result + len, "(%d - %d + %d) / %d = %d \n", v, x, y, u,
				total_points));

	/*
	 * (x/y+u)*v
	 */

	/*
	 * x*y*u+v   y*u*v+x   u*v*x+y   v*x*y+u
	 * x*y*u-v   y*u*v-x   u*v*x-y   v*x*y-u
	 * x*y/u+v   y*u/v+x   u*v/x+y   v*x/y+u
	 * y*u/x+v   u*v/y+x   v*x/u+y   x*y/v+u
	 * u*x/y+v   v*y/u+x   x*u/v+y   y*v/x+u
	 * x*y/u-v   y*u/v-x   u*v/x-y   v*x/y-u
	 * y*u/x-v   u*v/y-x   v*x/u-y   x*y/v-u
	 * u*x/y-v   v*y/u-x   x*u/v-y   y*v/x-u */
	if ((x * y * u + v == total_points))
		(len += sprintf(result + len, "%d * %d * %d + %d = %d \n", x, y, u, v,
				total_points));
	if ((y * u * v + x == total_points))
		(len += sprintf(result + len, "%d * %d * %d + %d = %d \n", y, u, v, x,
				total_points));
	if ((u * v * x + y == total_points))
		(len += sprintf(result + len, "%d * %d * %d + %d = %d \n", u, v, x, y,
				total_points));
	if ((v * x * y + u == total_points))
		(len += sprintf(result + len, "%d * %d * %d + %d = %d \n", v, x, y, u,
				total_points));
	if ((x * y * u - v == total_points))
		check2("**-", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d * %d - %d = %d \n", x,
						y, u, v, total_points));
	if ((y * u * v - x == total_points))
		check2("**-", y, u, v, x)
				&& (len += sprintf(result + len, "%d * %d * %d - %d = %d \n", y,
						u, v, x, total_points));
	if ((u * v * x - y == total_points))
		check2("**-", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d * %d - %d = %d \n", u,
						v, x, y, total_points));
	if ((v * x * y - u == total_points))
		check2("**-", v, x, y, u)
				&& (len += sprintf(result + len, "%d * %d * %d - %d = %d \n", v,
						x, y, u, total_points));
	if ((x * y / u + v == total_points) && DIV(x * y, u))
		check2("*/+", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", x,
						y, u, v, total_points));
	if ((y * u / v + x == total_points) && DIV(y * u, v))
		check2("*/+", y, u, v, x)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", y,
						u, v, x, total_points));
	if ((u * v / x + y == total_points) && DIV(u * v, x))
		check2("*/+", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", u,
						v, x, y, total_points));
	if ((v * x / y + u == total_points) && DIV(v * x, y))
		check2("*/+", v, x, y, u)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", v,
						x, y, u, total_points));
	if ((y * u / x + v == total_points) && DIV(y * u, x))
		check2("*/+", y, u, x, v)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", y,
						u, x, v, total_points));
	if ((u * v / y + x == total_points) && DIV(u * v, y))
		check2("*/+", u, v, y, x)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", u,
						v, y, x, total_points));
	if ((v * x / u + y == total_points) && DIV(v * x, u))
		check2("*/+", v, x, u, y)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", v,
						x, u, y, total_points));
	if ((x * y / v + u == total_points) && DIV(x * y, v))
		check2("*/+", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", x,
						y, v, u, total_points));
	if ((u * x / y + v == total_points) && DIV(u * x, y))
		check2("*/+", u, x, y, v)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", u,
						x, y, v, total_points));
	if ((v * y / u + x == total_points) && DIV(v * y, u))
		check2("*/+", v, y, u, x)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", v,
						y, u, x, total_points));
	if ((x * u / v + y == total_points) && DIV(x * u, v))
		check2("*/+", x, u, v, y)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", x,
						u, v, y, total_points));
	if ((y * v / x + u == total_points) && DIV(y * v, x))
		check2("*/+", y, v, x, u)
				&& (len += sprintf(result + len, "%d * %d / %d + %d = %d \n", y,
						v, x, u, total_points));
	if ((x * y / u - v == total_points) && DIV(x * y, u))
		check2("*/-", x, y, u, v)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", x,
						y, u, v, total_points));
	if ((y * u / v - x == total_points) && DIV(y * u, v))
		check2("*/-", y, u, v, x)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", y,
						u, v, x, total_points));
	if ((u * v / x - y == total_points) && DIV(u * v, x))
		check2("*/-", u, v, x, y)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", u,
						v, x, y, total_points));
	if ((v * x / y - u == total_points) && DIV(v * x, y))
		check2("*/-", v, x, y, u)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", v,
						x, y, u, total_points));
	if ((y * u / x - v == total_points) && DIV(y * u, x))
		check2("*/-", y, u, x, v)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", y,
						u, x, v, total_points));
	if ((u * v / y - x == total_points) && DIV(u * v, y))
		check2("*/-", u, v, y, x)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", u,
						v, y, x, total_points));
	if ((v * x / u - y == total_points) && DIV(v * x, u))
		check2("*/-", v, x, u, y)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", v,
						x, u, y, total_points));
	if ((x * y / v - u == total_points) && DIV(x * y, v))
		check2("*/-", x, y, v, u)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", x,
						y, v, u, total_points));
	if ((u * x / y - v == total_points) && DIV(u * x, y))
		check2("*/-", u, x, y, v)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", u,
						x, y, v, total_points));
	if ((v * y / u - x == total_points) && DIV(v * y, u))
		check2("*/-", v, y, u, x)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", v,
						y, u, x, total_points));
	if ((x * u / v - y == total_points) && DIV(x * u, v))
		check2("*/-", x, u, v, y)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", x,
						u, v, y, total_points));
	if ((y * v / x - u == total_points) && DIV(y * v, x))
		check2("*/-", y, v, x, u)
				&& (len += sprintf(result + len, "%d * %d / %d - %d = %d \n", y,
						v, x, u, total_points));

	/*
	 * x/(y*u)+v y/(u*v)+x u/(v*x)+y v/(x*y)+u
	 * y/(u*x)+v u/(v*y)+x v/(x*u)+y x/(y*v)+u
	 * u/(x*y)+v v/(y*u)+x x/(u*v)+y y/(v*x)+u */
	if (x / (y * u) + v == total_points && DIV(x, y * u))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", x, y, u, v,
				total_points));
	if (y / (u * v) + x == total_points && DIV(y, u * v))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", y, u, v, x,
				total_points));
	if (u / (v * x) + y == total_points && DIV(u, v * x))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", u, v, x, y,
				total_points));
	if (v / (x * y) + u == total_points && DIV(v, x * y))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", v, x, y, u,
				total_points));
	if (y / (u * x) + v == total_points && DIV(y, u * x))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", y, u, x, v,
				total_points));
	if (u / (v * y) + x == total_points && DIV(u, v * y))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", u, v, y, x,
				total_points));
	if (v / (x * u) + y == total_points && DIV(v, x * u))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", v, x, u, y,
				total_points));
	if (x / (y * v) + u == total_points && DIV(x, y * v))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", x, y, v, u,
				total_points));
	if (u / (x * y) + v == total_points && DIV(u, x * y))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", u, x, y, v,
				total_points));
	if (v / (y * u) + x == total_points && DIV(v, y * u))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", v, y, u, x,
				total_points));
	if (x / (u * v) + y == total_points && DIV(x, u * v))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", x, u, v, y,
				total_points));
	if (y / (v * x) + u == total_points && DIV(y, v * x))
		(len += sprintf(result + len, "%d / (%d * %d) + %d = %d \n", y, v, x, u,
				total_points));
}

void test_24(int x, int y, int u, int v, int total_points) {
	two_op_two(x, y, u, v, total_points);
	two_op_two(x, u, y, v, total_points);
	two_op_two(x, v, y, u, total_points);
	triple_op(x, y, u, v, total_points);
}

JNIEXPORT jstring JNICALL Java_com_example_twentyfour_JniClient_getCards(
		JNIEnv *env, jclass cls, jint a, jint b, jint c, jint d,
		jint total_points) {
	int i;
	for (i = 0; i < MAX; i++)
		formulas[i][0] = '\0';

	len = 0;
	test_24(a, b, c, d, total_points);
	if (len)
		return (*env)->NewStringUTF(env, result);
	else
		return (*env)->NewStringUTF(env, "我算不出来了 ^_^ \n");
}

#ifdef __cplusplus
}
#endif
