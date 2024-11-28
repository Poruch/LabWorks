using System;
using System.Diagnostics.Tracing;
using System.Threading;
using System.Xml.Serialization;

namespace MyTypes
{
    internal class MyString : Collection<char>
    {
        static readonly MyString points = new MyString() {' ',';', ',', ':' };
        static readonly MyString ends = new MyString() { '.', '?', '!' };
        public class Sentence
        {
            public int Count { get => words.Count; }
            Collection<MyString> words = new Collection<MyString>();
            Collection<MyString> points = new Collection<MyString>();
            public Sentence(Collection<MyString> words, Collection<MyString> points)
            {
                this.words = words;
                this.points = points;
            }
            public void Write()
            {
                for (int i = 0; i < words.Count; i++) 
                {
                    if (words[i].Count == i + 1)
                    {
                        words[i].Reverse();
                        Console.ForegroundColor = ConsoleColor.Red;
                    }
                    Console.Write(words[i].ToString() );
                    Console.ForegroundColor= ConsoleColor.White;
                    Console.Write(points[i].ToString());
                }
            }
            public MyString this[int i] 
            { 
                get
                {
                    return words[i];
                }
                set
                { 
                    words[i] = value; 
                }
            }
        }
        public MyString(Collection<char> chars) : base(chars.GetData())
        {
            //Console.WriteLine("Создалась строка!!!");
        }
        public MyString(char[] chars) : base(chars)
        {
            //Console.WriteLine("Создалась строка!!!");
        }
        public MyString() : base()
        {
            //Console.WriteLine("Создалась строка!!!");
        }
        public MyString(string chars) : base()
        {
            //Console.WriteLine("Создалась строка!!!");
            int p = 2;
            while (p < chars.Length) p *= 2;
            items = new char[p];
            for (int i = 0; i < chars.Length; i++)
                items[i] = chars[i];
            Count = chars.Length;
        }
        public bool Contains(char value)
        {
            for (int i = 0; i < Count; i++)
            {
                if (items[i] == value)
                    return true;
            }
            return false;
        }
        public Collection<Sentence> GetSentence()
        {
            Collection<Sentence> res = new Collection<Sentence>();
            int last = 0;
            Collection<MyString> _points = new Collection<MyString>();
            Collection<MyString> words = new Collection<MyString>();
            for (int i = 0; i < Count; i++)
            {
                if (ends.Contains(items[i]))
                {
                    words.Add(new MyString(Copy(last, i)));
                    _points.Add(new MyString() { items[i] });
                    res.Add(new Sentence(words, _points));
                    words = new Collection<MyString>();
                    _points = new Collection<MyString>();
                    last = i + 1;
                }
                else if (points.Contains(items[i]))
                {
                    _points.Add(new MyString());
                    words.Add(new MyString(Copy(last, i)));                    
                    while (points.Contains(items[i])) 
                        _points[_points.Count -1 ].Add(items[i++]);
                    last = i;
                }
            }
            
            return res;
        }      
        
        public override string ToString()
        {
            return new string(items);
        }
    }
}
