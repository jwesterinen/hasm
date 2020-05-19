/*
 *  stdlib header
 */

void ResetSys();
void DelayMs(int ms);
int Multiply(int multiplier, int multiplicand);
int Divide(int dividend, int divisor);
int ReadKey();
void SetLed(int state);
void SetGpioDir(int dir);
void SetGpio(int state);
int GetGpio();
void ExprPush(int expr);
int ExprPop();
int ExprTop();
void ExprPut(int expr);
void ClearDisplay();
int Getsd();
void Printsd(int value);
void AppendNum3(int value);

