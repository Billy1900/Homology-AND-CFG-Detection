//
//  display.cpp
//  SATsolver
//
//  Created by 袁博实 on 2019/1/31.
//  Copyright © 2019 袁博实. All rights reserved.
//
//  显示模块
//

#include <stdio.h>
#include "SATsolver.h"

/*
 * 函数名称: displayMenu
 * 接受参数: void
 * 函数功能: 显示主菜单
 * 返回值: void
 */
void displayMenu(void) {
    printf("----主菜单----\n");
    printf("1: 求解SAT问题\n");
    printf("2: 优化解SAT问题\n");
    printf("3: 数独(读取文件)\n");
    printf("4: 数独(程序生成)\n");
    printf("0: 退出\n");
    printf("\n请选择:");
}

/*
 * 函数名称: cnfVerify
 * 接受参数: void
 * 函数功能: 提示用户并验证cnf
 * 返回值: void
 */
void cnfVerify(void) {
    int op;
    printf("cnf解析完成!是否需要验证?\n[0:不验证/1:验证]:");
    scanf("%d",
          
          
          &op);
    if (op) {
        printf("读入的cnf如下:\n");
        printList(head);
    }
}

/*
 * 函数名称: displayResult
 * 接受参数: 指示是否有解的布尔值solved
 * 函数功能: 显示求解结果
 * 返回值: void
 */
void displayResult(bool solved) {
    if (solved) {
        printf("求解成功!结果如下:\n");
        for (int i = 1; i <= boolCount; i++)printf("%d ", value[i-1] ? i : -i)putchar('\n');} else {
        printf("该SAT不可满足!\n");
    }
    printf("DPLL过程用时:%u ms\n", timeUsed);
}

/*
 * 函数名称: printList
 * 接受参数: void
 * 函数功能: 打印当前的cnf范式
 * 返回值: void
 */
void printList(List printHead) {
    List clauseTail, literalTail;
    clauseTail = printHead;
    while (clauseTail->nextClause) {
        clauseTail = clauseTail->nextClause;
        literalTail = clauseTail;
        while (literalTail->nextLiteral) {
            literalTail = literalTail->nextLiteral;
            printf("%d ", literalTail->literal);
        }
        printf("0\n");
    }
    printf("\n");
}

/*
 * 函数名称: displaySudoku
 * 接受参数: void
 * 函数功能: 打印当前的数独
 * 返回值: void
 */
void displaySudoku(void) {
    int x, y;
    for (x = 0; x < 9;  x++) {
        for (y = 0; y < 9; y++) {
            if (sudoku[x][y])
                printf("%d ", sudoku[x][y] > 0 ? sudoku[x][y] : -sudoku[x][y]);
            else
                printf(". ");
        }
        putchar('\n');
    }
}

