#pragma once

namespace MyTypes {

    template<typename T>
    class MyList {
    private:
        using Criterion = bool (*)(T);
        int length;
    protected:
        T* items;
        void inBorder(int ind) {

        }
        void SetSize(int size)
        {

        }
    public:
        int Count;
        MyList(int size) {
            items = new T[size];
        }
        MyList() {
            items = new T[0];
        }
        MyList(T* newItems) {
            items = newItems;
        }

        ~MyList() {
            delete[] items;
        }
        void DeleteElem(int ind) {

        }
        void Insert(int ind, MyList<T> array) {

        }
        void DeleteElem(Criterion criterion) {

        }

        void Reverse() {

        }
        void Move(int count, bool right = true) {

        }

        void Add(int ind, T value) {

        }
        void Add(T value) {

        }
        void Clear() {
            for (int i = 0; i < Count; i++) {
                items[i] = default;
            }
        }


        MyList<T> Copy(int indS) {
            MyList result = MyList(length);
            for(int i =)
        }
        MyList<T> Copy(int indS, int indE);

        T FindFirst(Criterion criterion);
        T FindLast(Criterion criterion);
        MyList<T> FindAll(Criterion criterion);

        T* GetData() {
            return items;
        }

        const T& operator [](size_t i) const
        {
            return items[i];
        }
        T& operator [](size_t i) {
            return items[i];
        }
    };
}