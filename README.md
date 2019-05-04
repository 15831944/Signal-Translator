# Signal-Translator
## Задание для В.8

![alt-text](https://pp.userapi.com/c850416/v850416346/35202/XtGJ4RSXC_8.jpg)
```
1. <signal-program> --> <program>
2. <program> --> PROCEDURE <procedureidentifier><parameters-list> ; <block> ; 
3. <block> --> <declarations> BEGIN <statementslist> END 
4. <statements-list> --> <empty> 
5. <parameters-list> --> ( <declarations-list> ) |  <empty> 
6. <declarations> --> <variable-declarations> 
7. <variable-declarations> --> VAR <declarationslist>  | <empty> 
8. <declarations-list> --> <declaration> <declarations-list> | <empty> 
9. <declaration> --><variableidentifier><identifierslist>:<attribute><attributes-list> ; 
10. <identifiers-list> --> , <variable-identifier> <identifiers-list> | <empty> 
11. <attributes-list> --> <attribute> <attributeslist> | <empty> 
12. <attribute> --> SIGNAL     | COMPLEX    | INTEGER    | FLOAT      | BLOCKFLOAT | EXT 
13. <variable-identifier> --> <identifier> 
14. <procedure-identifier> --> <identifier>  
15. <identifier> --> <letter><string> 
16. <string> --> <letter><string> | <digit><string> | <empty> 
17. <digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
18. <letter> --> A | B | C | D | ... | Z 
```
