using DataManage;
using MyTypes;
using System;
using System.Threading;

namespace lab_9
{
    internal class MyIntarface
    {
        public delegate void Block();
        static int count;
        public static bool Intarface(MyCollection<Tuple<string, Block>> blocks)
        {            
            count++;
            Console.WriteLine("Любое число кроме этих - " + (count == 1 ? "выход из программы":"выход к предыдущему циклу"));
            for (int i = 0; i < blocks.Count; i++)
            {
                Console.WriteLine((i + 1).ToString() + " " + blocks[i].Item1);
            }
            int number = InputManager.ReadValueUInt();
            if (number <= 0 || number > blocks.Count)
            {
                count--;
                return false;
            }
            blocks[number - 1].Item2.Invoke();

            return true;
        }
    }
}
