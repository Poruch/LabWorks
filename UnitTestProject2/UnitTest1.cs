using DataManage;
using lab_9;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MyTypes;
using System;
using System.ComponentModel;

namespace UnitTestProject2
{
    [TestClass]
    public class UnitTestForLab9
    {
        [TestMethod]
        public void TestCreatingStudentsAndBasicProperties()
        {
            //Arange
            Student student = new Student();
            Student student2 = new Student(student);
            Student student1 = new Student("Антон", 10, 10);

            //Act
            student.Age = 20;
            student1.Age = 19;
            student2.Age = 10;

            student.Gpa = 41;
            student1.Gpa = -3;
            student2.Gpa = 9;

            student.Name = "Dan";

            //Assert
            Assert.AreEqual(student.Age, 20);
            Assert.AreEqual(student1.Age, 19);
            Assert.AreEqual(student2.Age, 10);

            Assert.AreEqual(student.Gpa, 10);
            Assert.AreEqual(student1.Gpa, 0);
            Assert.AreEqual(student2.Gpa, 9);

            Assert.AreEqual(student.Name, "Dan");
            Assert.AreEqual(student1.Name, "Антон");
            Assert.AreEqual(student2.Name, "NoName");
        }


        [TestMethod]
        public void TestBasicOperationWithStudents()
        {
            //Arange
            Student student1 = new Student("Олег",18,6);
            Student student2 = new Student("АНДРей",19,7);

            //Act
            student1 = ~student1;
            student2 = ~student2;

            ++student1;

            Assert.AreEqual(Student.GetCompare(student1,student2), "Студент Олег ровесник студента Андрей\n" + $"GPA студента Олег меньше GPA студента Андрей");

            int course = (int)student1;

            bool good = student2;

            Student student3 = student1 % "ДАрья";
            student2 = student2 - 5;
            int hash = student3.GetHashCode();

            //Assert
            Assert.AreEqual(student1.Name, "Олег");
            Assert.AreEqual(student2.Name, "Андрей");

            Assert.AreEqual(student1.Age,19);
            Assert.AreEqual(student2.Age, 19);

            Assert.AreEqual(course, 2);

            Assert.IsTrue(good);

            Student student4 = new Student(student1);
            student4.Name = "Дарья";
            Assert.AreEqual(~student3, student4);

            Assert.AreEqual(student2.Gpa, 2);
            student2 = student2 - 9;
            Assert.AreEqual(student2.Gpa, 0);
        }


        [TestMethod]
        public void TestMassiveStudents()
        {
            //Arrange
            StudentArray studentArray = new StudentArray
            {
                //Act
                new Student(),
                new Student(),
                new Student(),
                new Student(),
                new Student()
            };

            
            studentArray.Add(new Student());

            Student student = studentArray[0];
            student.Name = "Валера";
            Assert.AreEqual(student, studentArray[0]);
            Assert.AreEqual(studentArray.Count, 6);
            StudentArray array2 = new StudentArray(studentArray.Copy(1, 2));
            array2[0].Name = "Рак";
            Assert.AreNotEqual(studentArray[1], array2[0]);

            StudentArray studentArray1 = new StudentArray(studentArray.Copy(0));

            Assert.AreNotEqual(studentArray1, studentArray);


            Assert.AreEqual(StudentArray.countArrayes,3);
            array2 = new StudentArray();

            Assert.AreEqual(StudentArray.countArrayes, 4);
            array2.Add(new Student());
            array2.DeleteElem(0);
            Assert.AreEqual(StudentArray.countArrayes, 4);
            array2.Add(new Student());
            array2.Add(new Student());
            array2.DeleteElem(1);
            Assert.AreEqual(array2.Count, 1);

            Assert.IsTrue(array2.InBorder(0));

            array2.Add(new Student());
            array2.Add(new Student());
            array2.Add(new Student());
            array2.Add(new Student());
            array2.Move(10);
            Student s = array2.GetTHEFIRST();
            array2[2].Gpa = 8;
            array2[2].Age = 20;
            Student s2 = array2.GetTHEFIRST();
            Assert.AreNotEqual(s, s2);

            StudentArray array3 = new StudentArray()
            {
                new Student(),
                new Student()
            };
            
            Assert.AreEqual((int)array3[0],-1);
            studentArray = new StudentArray(); 
            studentArray.Insert(0, InputManager.GetStudentsFromFile("F:\\Вшэ\\LabWorks\\lab#9\\Students.txt"));

            Assert.AreEqual(array3.ToString(), "1 " + array3[0] + "\n"+ "2 "+ array3[1] + "\n");

            //Assert
            Assert.AreEqual(1, 1);
        }
        [TestMethod]
        public void TestMyCollection()
        {
            MyCollection<int> array = new MyCollection<int>()
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9,
            };

            array.Add(1,10);
            array.Add(2,20);
            array.Add(3,30);
            array.Move(10);
            array.Insert(0, new MyCollection<int>() { 1, 2, 3, 4, 5, 6 });
            array.Add(10);

            int defaul2 = array.FindLast((int x) => { return x % 2 == 100000000; });
            int first = array.FindFirst((int x) => { return x % 2 == 0; });           
            int last = array.FindLast((int x) => { return x % 2 == 0; });

            array.DeleteElems((int x) => { return x % 2 == 0; });
            int defaul = array.FindFirst((int x) => { return x % 2 == 0; });
            int[] data = array.GetData();
            array.Reverse();
            Array.Reverse(data);


            for (int i = 0; i < data.Length; i++)
            {
                Assert.AreEqual(data[i], array[i]);
            }

            Assert.AreEqual(defaul,0);
            Assert.AreEqual(defaul2, 0);
            Assert.AreEqual(first, 2);
            Assert.AreEqual(last, 10);



        }
        [TestMethod]
        public void TestMyMath() 
        {
            Assert.AreEqual(MyMath.Clamp(0,-10,10),0);
            Assert.AreEqual(MyMath.Clamp(20, -10, 10), 10);
            Assert.AreEqual(MyMath.Clamp(-20, -10, 10),-10);

            Assert.AreEqual(MyMath.Clamp(0d, -10d, 10d), 0d);
            Assert.AreEqual(MyMath.Clamp(20d, -10d, 10d), 10d);
            Assert.AreEqual(MyMath.Clamp(-20d, -10d, 10d), -10d);
        }
    }
}
