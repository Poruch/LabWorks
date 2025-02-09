using System;
using System.Xml.Schema;

namespace MyTypes
{
    public class StudentArray : MyCollection<Student>
    {
        public static int countArrayes = 0;
        public StudentArray(MyCollection<Student> collection) : base(collection) { countArrayes++; }
        public StudentArray() : base() { countArrayes++; }

        ~StudentArray() { countArrayes--; }
        public Student GetTHEFIRST()
        {
            var students = FindAll((Student s) => { return s.Gpa > 8; });
            Student THEFIRST = new Student();
            for (int i = 0;i < students.Count; i++)
            {
                if(THEFIRST.Age < students[i].Age)
                    THEFIRST = students[i];
            }
            return THEFIRST;
        }

        public override string ToString()
        {
            string s = "";
            int count = 1;
            if(this != null)
            foreach(Student student in this)
            {
                 s += count++ + " " + (student.ToString()) + "\n";
            }
            return s;
        }
    }
}
