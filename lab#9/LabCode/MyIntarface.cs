using DataManage;
using MyTypes;
using System;

namespace lab_9
{
    public class MyIntarface
    {
        public delegate void Block();
        static int count = 0;
        public static bool Intarface(MyCollection<Tuple<string, Block>> blocks)
        {            
            count++;
            Console.WriteLine("Любое число кроме представленных ниже - " + (count == 1 ? "выход из программы":"выход к предыдущему циклу"));
            for (int i = 0; i < blocks.Count; i++)
            {
                Console.WriteLine((i + 1).ToString() + " " + blocks[i].Item1);
            }
            int number = InputManager.ReadValueUInt();
            if (number <= 0 || number > blocks.Count)
            {
                count -= 2;
                return false;
            }
            blocks[number - 1].Item2.Invoke(); 
            Console.WriteLine("Нажмите Enter для продолжения...");
            Console.ReadLine();
            return true;
        }
    }
}
