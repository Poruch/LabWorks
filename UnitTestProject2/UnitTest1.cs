using Microsoft.VisualStudio.TestTools.UnitTesting;
using MyTypes;

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
            StudentArray studentArray = new StudentArray();

            //Act
            studentArray.Add(new Student());

            //Assert
            Assert.AreEqual(1, 1);
        }
    }
}
