using System;
using System.Collections.Generic;

namespace MachineTuring
{
    internal class Program
    {
        //Константы
        const int startPosition = 0;
        const int startState = 1;
        const int lastState = 0;

        //Переменные
        static int currentPosition = 0;
        static int currentState = 0;

        //Упр. Таблица
        static Cell[,] table;

        public struct Cell
        {
            public Cell(char sym,int dir,int state)
            {
                direction = dir;
                this.state = state;
                symbol = sym;
            }
            public int direction;
            public int state;
            public char symbol;
        }
        static void Main(string[] args)
        {

            Console.WriteLine("Привет я могу выполнять таблицы для машины Тьюринга, введите сроку");
            //Инициализация переменных
            List<char> line = new List<char>(Console.ReadLine());
            string letters = "|^";            
            var empty = letters[letters.Length - 1];
            table = new Cell[letters.Length, 4];
            currentState = startState;
            currentPosition = startPosition;

            // (|*N)^(|*K) = ^|*(N+K)
            // Загрузка таблицы
            table[0, 1] = new Cell(empty,1,2);
            table[0, 2] = new Cell('|',1,2);
            table[0, 3] = new Cell('|', -1,3);

            table[1,2] = new Cell('|', -1, 3);
            table[1,3] = new Cell('^', 1, 0);
            //
           
            
            //Для бесконечных программ
            int indexer = 0;


            //Основной цикл
            while (currentState != lastState && indexer < 10000000)
            {
                if (currentPosition < 0)
                {
                    line.Insert(0, '^');
                    currentPosition = 0;
                }
                if (currentPosition == line.Count) 
                {
                    line.Add('^');
                }
                Cell currentCell = table[letters.IndexOf(line[currentPosition]), currentState];
                line[currentPosition] = currentCell.symbol;
                currentPosition += currentCell.direction;
                currentState = currentCell.state;
                indexer++;
            }

            //Вывод полученной строки
            foreach (char c in line)
            Console.Write(c);
            Console.ReadLine();
        }
    }
}
