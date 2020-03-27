# nx-TAS

Scripting documentation for [nx-TAS](https://github.com/hamhub7/nx-TAS).

## Grammar Definition

```lbnf
comment "#" ;
P. Program ::= [Command] ;

terminator Command ";" ;

CAddController.    Command ::= "+ " Ident " " ControllerType ;
CRemoveController. Command ::= "- " Ident ;
CSetButton.        Command ::= "] " Ident " " [Button] ;
CUnsetButton.      Command ::= "[ " Ident " " [Button] ;
CWait.             Command ::= "! " Integer ;
CImport.           Command ::= "$ " String ;

CTProController. ControllerType ::= "pro_controller " Color " " Color " " Color " " Color ;

COLRgb. Color ::= "rgb(" Integer "," Integer "," Integer ")" ;

separator Button "," ;

BButtonA.       Button ::= "A" ;
BButtonB.       Button ::= "B" ;
BButtonX.       Button ::= "X" ;
BButtonY.       Button ::= "Y" ;
BBumperL.       Button ::= "L" ;
BBumperR.       Button ::= "R" ;
BBumperSLLeft.  Button ::= "SLL" ;
BBumperSRLeft.  Button ::= "SRL" ;
BBumperSLRight. Button ::= "SLR" ;
BBumperSRRight. Button ::= "SRR" ;
BTriggerZL.     Button ::= "ZL" ;
BTriggerZR.     Button ::= "ZR" ;
BDpadUp.        Button ::= "DU" ;
BDpadDown.      Button ::= "DD" ;
BDpadLeft.      Button ::= "DL" ;
BDpadRight.     Button ::= "DR" ;
BStickLeft.     Button ::= "LS" ;
BStickRight.    Button ::= "RS" ;
BPlus.          Button ::= "PLUS" ;
BMinus.         Button ::= "MINUS" ;
```

### Extra Syntax Rules

Due to the `comment` and `terminator` rules in the grammar, valid scripts will look like:
```
commandA ; commandB ;

commandC ;
# comment
commandD ;
commandE ; commandF ; commandG ;
```

## Commands

### Controller Management

```lbnf
CAddController.    Command ::= "+ " Ident " " ControllerType ;
CRemoveController. Command ::= "- " Ident ;
```

To add controllers, use the `+` command:
```
+ mario pro_controller rgb(255,0,0) rgb(255,255,255) rgb(255,0,0) rgb(255,0,0)
```
This creates a controller with a red body, white buttons, and red left and right grips respectively. It will be referred to as `mario` until it is removed.

To remove controllers, use the `-` command:
```
- mario
```

### Button Management

```lbnf
CSetButton.        Command ::= "] " Ident " " [Button] ;
CUnsetButton.      Command ::= "[ " Ident " " [Button] ;
```

To set buttons, use the `]` command:
```
] mario A,B,X,Y
```

To unset buttons, use the `[` command:
```
[ mario A,B,X,Y
```

Most button names are simple, however the DPAD is listed as `DU` for DPAD-Up, `DD` for DPAD-Down, `DR` for DPAD-Right, and `DL` for DPAD-Left.

### Wait Frames

```lbnf
CWait.             Command ::= "! " Integer ;
```

To wait a certain amount of frames, use the `!` command:
```
! 5
```

## Variables

TODO

## Functions

TODO
