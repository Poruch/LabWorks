using System;
using System.Collections;
namespace MyTypes
{
    delegate T Criterion<T, J>(J a);
    class MyCollection<T> : IEnumerable, IEnumerator
    {
        private int length;
        protected T[] items;
        public int Count
        {
            get { return length; }
            protected set { length = value; }
        }
        public MyCollection(int size)
        {
            int p = 2;
            while (p < size) p *= 2;
            items = new T[p];
            length = size;
        }
        public MyCollection(MyCollection<T> collection)
        {
            items = new T[collection.Count];
            for (int i = 0; i < collection.Count; i++)
            {
                items[i] = collection[i];
            }
            length = collection.length;
        }
        public MyCollection()
        {
            items = new T[0];
            length = 0;
        }
        public MyCollection(T[] numbers)
        {
            int p = 2;
            while (p < numbers.Length) p *= 2;
            items = new T[p];
            for (int i = 0; i < numbers.Length; i++)
                items[i] = numbers[i];
            length = numbers.Length;
        }
        protected int inBorder
        {
            set
            {
                if (!(value < length && value >= 0))
                    throw new ArgumentOutOfRangeException("Выход за границы коллекции типа - " + typeof(T).Name);
            }
        }
        public bool InBorder(int value)
        {  
                return value < length && value >= 0;
        }
        protected void SetSize(int size)
        {
            var result = new T[size];
            for (int i = 0; i < (length > size ? size : length); i++)
                result[i] = items[i];
            items = result;
        }


        public void DeleteElem(int ind)
        {
            try { inBorder = ind; }
            catch
            {
                Console.WriteLine("Удаление элемента невозможно, выход за границы массива");
                return;
            }
            int j = 0;
            Console.WriteLine("Удален элемент - " + items[ind].ToString());
            for (int i = 0; i < ind; i++)
            {
                items[j++] = items[i];
            }
            for (int i = ind + 1; i < length; i++)
            {
                items[j++] = items[i];
            }
            length--;
            int newLen = 1;
            while (newLen <= length)
                newLen *= 2;
            SetSize(newLen);
        }
        public void Insert(int ind, MyCollection<T> array)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            if(items.Length == 0)
            {
                items = array.items;
                length = array.length;
                return;
            }
            int newLen = items.Length;
            while (length + array.Count >= newLen)
                newLen *= 2;
            SetSize(newLen);

            for (int i = length + array.Count; i >= ind + array.Count; i--)
                items[i] = items[i - array.Count];
            for (int i = ind; i < array.Count; i++)
                items[i] = array[i - ind];
            length += array.Count;
        }
        public void DeleteElem(Criterion<bool, T> criterion)
        {
            var currarray = new T[length];
            int count = 0;
            Console.Write("Удалены элементы - ");
            for (int i = 0; i < length; i++)
            {
                if (!criterion(items[i]))
                    currarray[count++] = items[i];
                else
                    Console.Write(items[i].ToString() + " ");
            }
            Console.WriteLine();
            for (int i = 0; i < count; i++)
            {
                items[i] = currarray[i];
            }
            int newLen = 1;
            while (newLen <= count)
                newLen *= 2;
            SetSize(newLen);
            length = count;
        }

        public void Reverse()
        {
            T[] result = new T[items.Length];
            int j = length - 1;
            for (int i = 0; i < length; i++)
                result[i] = items[j--];
            items = result;
        }

        public void Add(int ind, T value)
        {
            if (!(ind <= length && ind >= 0))
            {
                Console.WriteLine("Ошибка в количестве добавляемых элементов");
                return;
            }
            int newLen = 1;
            while (length + 1 > newLen)
                newLen *= 2;
            SetSize(newLen);

            for (int i = length; i > ind; i--)
            {
                items[i] = items[i - 1];
            }
            items[ind] = value;
            length++;
        }
        public void Add(T value)
        {
            int newLen = 1;
            while (length + 1 > newLen)
                newLen *= 2;
            SetSize(newLen);
            items[length] = value;
            length++;
        }
        public void Clear()
        {
            for (int i = 0; i < length; i++)
                items[i] = default;
        }

        public void Move(int count, bool right = true)
        {
            if (length == 0)
                return;
            count = count % length;
            T[] result = new T[items.Length];
            int k = 0;
            if (right)
            {
                for (int i = length - count; i < length; i++)
                    result[k++] = items[i];
                for (int i = 0; i < length - count; i++)
                    result[k++] = items[i];
            }
            else
            {
                for (int i = count; i < length; i++)
                    result[k++] = items[i];
                for (int i = 0; i < count; i++)
                    result[k++] = items[i];
            }
            items = result;
        }


        public MyCollection<T> Copy(int indS)
        {
            try { inBorder = indS; }
            catch
            {
                Console.WriteLine("Копирование невозможно, выход за границы массива");
                return new MyCollection<T>(0);
            }
            MyCollection<T> result = new MyCollection<T>(Count - indS);
            for (int i = indS; i < Count; i++)
                result[i - indS] = items[i];
            return result;
        }
        public MyCollection<T> Copy(int indS, int indE)
        {
            try { inBorder = indS; }
            catch
            {
                Console.WriteLine("Копирование невозможно, выход за границы массива");
                return new MyCollection<T>(0);
            }
            indE = indE > Count ? Count : indE;
            MyCollection<T> result = new MyCollection<T>(indE - indS);
            for (int i = indS; i < indE; i++)
                result[i - indS] = items[i];
            return result;
        }
        public T FindFirst(Criterion<bool, T> criterion)
        {
            for (int i = 0; i < length; i++)
            {
                if (criterion(items[i]))
                {
                    return items[i];
                }
            }
            Console.WriteLine("Ни один элемент не подешел по критерию");
            return default;
        }
        public T FindLast(Criterion<bool, T> criterion)
        {
            for (int i = length; i >= 0; i--)
            {
                if (criterion(items[i]))
                {
                    return items[i];
                }
            }
            Console.WriteLine("Ни один элемент не подешел по критерию");
            return default;
        }
        public MyCollection<T> FindAll(Criterion<bool, T> criterion)
        {
            var currarray = new T[length];
            T[] result;
            int k = 0;
            for (int i = 0; i < length; i++)
                if (criterion(items[i]))
                    currarray[k++] = items[i];
            result = new T[k];
            for (int i = 0; i < k; i++)            
                result[i] = currarray[i];
            return new MyCollection<T>(result);
        }

        public T this[int key]
        {
            get
            {
                inBorder = key;
                return items[key];
            }
            set
            {
                inBorder = key;
                items[key] = value;
            }
        }

        public IEnumerator GetEnumerator()
        {
            return this;
        }

        public object Current
        {
            get
            {
                inBorder = index;
                return items[index];
            }
        }
        int index = -1;

        public bool MoveNext()
        {
            index++;
            if (index < Count && index > -1)
                return true;
            else
            {
                Reset();
                return false;
            }
        }

        public T[] GetData()
        {
            T[] result = new T[Count];
            for (int i = 0; i < Count; i++)
                result[i] = items[i];
            return result;
        }

        public void Reset()
        {
            index = -1;
        }
    }
}
