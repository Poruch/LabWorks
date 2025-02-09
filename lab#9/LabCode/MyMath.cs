using System;

namespace DataManage
{
    public class MyMath
    {
        public static int Clamp(int value, int minValue, int maxValue)
        {
            return Math.Max(Math.Min(value, maxValue),minValue);
        }

        public static double Clamp(double value, double minValue, double maxValue)
        {
            return Math.Max(Math.Min(value, maxValue), minValue);
        }
    }
}
