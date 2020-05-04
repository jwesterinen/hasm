/*
 *  stdlib header
 */

void ResetSys();
void DelayMs(ms);
int Multiply(multiplier, multiplicand);
int Divide(dividend, divisor);
int ReadKey();
void SetLed(state);
void SetGpioDir(dir);
void SetGpio(state);
int GetGpio();
void ExprPush(expr);
int ExprPop();
int ExprTop();
void ExprPut(expr);
void ClearDisplay();
int Getsd();
void Printsd(value);
void AppendNum3(value);

