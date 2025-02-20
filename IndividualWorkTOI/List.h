#pragma once
#include "MyRecord.h"
#define RECORD MyTypes::Image

namespace Lists {	
	template<int N>
	struct List {
	private:
		struct Node
		{
			Node* nextNode[N];
			int index = 0;
			RECORD* record;

			Node(int ind, RECORD im) {
				index = ind;
				record = new RECORD(im);				
			}
			Node() {
				index = 0;
				record = RECORD();
			}
			template <typename T>
			T GetValue(T(*criterion)(RECORD)) {
				return criterion(record);
			}

			bool operator==(const Node& node) {
				return record == node.record;
			}
		};
		Node* first[N+1];
		Node* last[N+1];
	public:
		typedef int (*Criterion)(RECORD);
		List(Criterion criterion[N]) {
			static_assert(N > 0," оличество критериев должно быть больше 0")
			for(size_t i = 0; i < N; i++)
				this->criterions[i] = criterions[i];
			count = 0;
		}
		int count;
		int Count() {
			return count;
		}

		bool IsEmpty() {
			bool result = true;
			for (int i = 0; i < N+1; i++) {
				result = result && (first[i] == nullptr);
			}
			return result;
		}

		bool IsEmpty(int ind) {			
			return first[ind] == nullptr;
		}

		Criterion criterions[N];
		void SortedPush(RECORD value);

		void PushBack(RECORD value);
		void Push(RECORD value);

		void RemoveFirst();
		void RemoveLast();


		void Remove(int value, int criterionInd);

		Node* operator[] (const int index);

		void WriteList();

		void ReverseIter();
		void ReverseRec();

		Node* GetReverseListIt(Node* root);
		Node* GetReverseListRec(Node* root);

		RECORD PopFirst();
		RECORD PopLast();

		void Remove(int value, int criterionInd);

		void WriteList();

		void WriteList(int criterionInd);

		RECORD Find(int value, int criterionId);
	};
};