#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"
#include "Edge.h"
#include "Place.h"
#include "DepthFirstVisit.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace MGGCPPUnitTests
{


	TEST_CLASS(UnitTest1)
	{
		Graph<Place, Edge> _graph;
		
	public:

		TEST_METHOD(Edge_ConstructorAndGetters)
		{
			Edge<string> e("s", "d", 3);
			Assert::IsTrue(e.getSource() == "s");
			Assert::IsTrue(e.getDestination() == "d");
			Assert::IsTrue(e.getWeight() == 3);
		}

		TEST_METHOD(Edge_ToString)
		{
			Edge<string> e("s", "d", 3);
			ostringstream stream;
			stream << e;
			string str = stream.str();
			Assert::IsTrue(str == "[s--3-->d]\n");
		}
		
		TEST_METHOD(AddAndRemoveVertex)
		{
			Town t("test");
			_graph.Add(t);
			Assert::IsTrue(_graph.Contains(t));
			Assert::IsTrue(_graph.Remove(t));
			Assert::IsTrue(!_graph.Contains(t));
			Assert::IsTrue(!_graph.Remove(t));
		}

		TEST_METHOD(stack) {
			//_graph.CheckAccess(2);

			Assert::IsTrue(true);
		}


		TEST_METHOD(AddGetRemoveEdges)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			vector<Edge<Place>> testEdges = { Edge<Place>(a, b, 1), Edge<Place>(b, c, 2), Edge<Place> (c, d, 3)};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}
			Assert::IsTrue(_graph.Contains(a));
			Assert::IsTrue(_graph.Contains(b));
			Assert::IsTrue(_graph.Contains(c));
			Assert::IsTrue(_graph.Contains(d));
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				Assert::IsTrue(_graph.Contains(*it));
			}

			vector<Edge<Place>> graphEdges = _graph.getEdges();
			Assert::IsTrue(testEdges.size() == graphEdges.size());
			Assert::IsTrue(equal(testEdges.begin(), testEdges.begin() + testEdges.size(), graphEdges.begin()));

			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				Assert::IsTrue(_graph.Remove(*it));
			}
			graphEdges = _graph.getEdges(); //TODO parlarne col prof
			Assert::IsTrue(graphEdges.size() == 0);
		}


		TEST_METHOD(InOutDegree)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			vector<Edge<Place>> testEdges = { 
				Edge<Place>(a, b, 1), 
				Edge<Place>(a, c, 2), 
				Edge<Place>(a, d, 3), 
				Edge<Place>(d, c, 4),
				Edge<Place>(b, c, 5),
			};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}
			Assert::IsTrue(_graph.Contains(a));
			Assert::IsTrue(_graph.Contains(b));
			Assert::IsTrue(_graph.Contains(c));
			Assert::IsTrue(_graph.Contains(d));
			Assert::IsTrue(_graph.GetOutDegree(a) == 3);
			Assert::IsTrue(_graph.GetOutDegree(b) == 1);
			Assert::IsTrue(_graph.GetOutDegree(c) == 0);
			Assert::IsTrue(_graph.GetOutDegree(d) == 1);
			Assert::IsTrue(_graph.GetInDegree(a) == 0);
			Assert::IsTrue(_graph.GetInDegree(b) == 1);
			Assert::IsTrue(_graph.GetInDegree(c) == 3);
			Assert::IsTrue(_graph.GetInDegree(d) == 1);
		}


		TEST_METHOD(GetVertexes)
		{
			vector<Place> ttowns = { Town("a"), Town("b"), Town("c"), Town("d"), Town("e") };
			for (auto it = ttowns.begin(); it != ttowns.end(); ++it) {
				_graph.Add(*it);
			}
			vector<Place> graphVertexes = _graph.getVertexes();
			Assert::IsTrue(ttowns.size() == graphVertexes.size());
			Assert::IsTrue(equal(ttowns.begin(), ttowns.begin() + ttowns.size(), graphVertexes.begin()));
		}


		TEST_METHOD(GetNeighborAndEdges)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			vector<Edge<Place>> testEdges = {
				Edge<Place>(a, b, 1),
				Edge<Place>(a, c, 2),
				Edge<Place>(a, d, 3),
				Edge<Place>(d, c, 4),
				Edge<Place>(b, c, 5),
			};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}
			Assert::IsTrue(_graph.Contains(a));
			Assert::IsTrue(_graph.Contains(b));
			Assert::IsTrue(_graph.Contains(c));
			Assert::IsTrue(_graph.Contains(d));
			vector<Place> graphNeighbors = _graph.GetNeighbors(a);
			vector<Place> testNeighbors = { b, c, d };
			Assert::IsTrue(graphNeighbors.size() == testNeighbors.size());
			Assert::IsTrue(equal(testNeighbors.begin(), testNeighbors.begin() + testNeighbors.size(), graphNeighbors.begin()));
			_graph.Add(Edge<Place>(a, b, 11));
			vector<Edge<Place>> graphEdgesFromAtoB = _graph.GetEdges(a, b);
			vector<Edge<Place>> graphEdgesFromCtoA = _graph.GetEdges(c,a);
			Assert::IsTrue(graphEdgesFromAtoB.size()==2);
			Assert::IsTrue(graphEdgesFromCtoA.size()==0);
		}


		TEST_METHOD(DepthFirstVisit)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			vector<Edge<Place>> testEdges = {
				Edge<Place>(a, b, 1),
				Edge<Place>(a, c, 2),
				Edge<Place>(a, d, 3),
				Edge<Place>(d, c, 4),
				Edge<Place>(b, c, 5),
			};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}
			vector<Place> dfv = _graph.DepthFirstVisit(a);
			Assert::IsTrue(true);
		}


		TEST_METHOD(Pippo)
		{
			Edge<std::string> e("ciao", "pollo", 5);
			map< int, vector<string> > m;
			m[0].push_back("ciao");
			m[0].push_back("salut");
			m[1].push_back("ciao1");
			m[1].push_back("salut1");

			for (auto iter = m.cbegin(); iter != m.cend(); ++iter) {
				vector<string> tmp = iter->second;
				for (unsigned int i = 0; i<tmp.size(); ++i) {
					cout << tmp[i] << endl;
				}
			}
			
			Assert::IsTrue(true);
		}


	};
}
