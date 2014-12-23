#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"
#include "Edge.h"
#include "Place.h"
#include "DijkstraAlgorithm.h"
#include "PriorityQueue.h"


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
			Assert::IsFalse(_graph.Contains(t));
			Assert::IsFalse(_graph.Remove(t));
		}

		TEST_METHOD(AddGetRemoveEdges)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			vector<Edge<Place>> testEdges = { Edge<Place>(a, b, 1), Edge<Place>(b, c, 2), Edge<Place>(c, d, 3) };
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
			Assert::IsFalse(_graph.Remove(testEdges[0]));
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
			vector<Edge<Place>> graphEdgesFromCtoA = _graph.GetEdges(c, a);
			Assert::IsTrue(graphEdgesFromAtoB.size() == 2);
			Assert::IsTrue(graphEdgesFromCtoA.size() == 0);
		}

		TEST_METHOD(DFSvisit)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			Town e("e");
			vector<Place> testVertexes = { a, d, c, e, b };
			vector<Edge<Place>> testEdges = {
				Edge<Place>(a, b, 1),
				Edge<Place>(c, e, 2),
				Edge<Place>(a, d, 3),
				Edge<Place>(d, c, 4),
				Edge<Place>(b, c, 5),
			};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}

			vector<Place> visitedVertexes;
			for (auto it = _graph.beginDFS(a); it != _graph.endDFS(); ++(*it)) {
				Place* t = (*it).visited;
				visitedVertexes.push_back(*t);
			}

			Assert::IsTrue(testVertexes.size() == visitedVertexes.size());
			Assert::IsTrue(equal(testVertexes.begin(), testVertexes.begin() + testVertexes.size(), visitedVertexes.begin()));
		}

		TEST_METHOD(BFSvisit)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			Town e("e");
			vector<Place> testVertexes = { a, b, d, c, e }; //BFS
			vector<Edge<Place>> testEdges = {
				Edge<Place>(a, b, 1),
				Edge<Place>(c, e, 2),
				Edge<Place>(a, d, 3),
				Edge<Place>(d, c, 4),
				Edge<Place>(b, c, 5),
			};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}

			vector<Place> visitedVertexes;
			for (auto it = _graph.beginBFS(a); it != _graph.endBFS(); ++(*it)) {
				Place* t = (*it).visited;
				visitedVertexes.push_back(*t);
			}

			Assert::IsTrue(testVertexes.size() == visitedVertexes.size());
			Assert::IsTrue(equal(testVertexes.begin(), testVertexes.begin() + testVertexes.size(), visitedVertexes.begin()));
		}

		TEST_METHOD(GraphException)
		{
			Town t = Town("t");
			unsigned long int v;

			v = _graph.GetVersion();
			_graph.Add(t);
			Assert::ExpectException<GraphVersionException>([&] { _graph.CheckVersion(v); });
			
			v = _graph.GetVersion();
			_graph.Remove(t);
			Assert::ExpectException<GraphVersionException>([&] { _graph.CheckVersion(v); });

			//BFS iter exception
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			Town e("e");
			vector<Place> testVertexes = { a, b, d, c, e }; //BFS
			vector<Edge<Place>> testEdges = {
				Edge<Place>(a, b, 1),
				Edge<Place>(c, e, 2),
				Edge<Place>(a, d, 3),
				Edge<Place>(d, c, 4),
				Edge<Place>(b, c, 5),
			};
			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}

			for (auto it = _graph.beginBFS(a); it != _graph.endBFS(); ++(*it)) {
				Place* vis = (*it).visited;
				if (vis->name == "c") {
					_graph.Add(t); // add a vertex during BFS
					Assert::ExpectException<GraphVersionException>([&] { it.operator*(); });
					break;
				}

			}

		}

		TEST_METHOD(Dijkstra)
		{
			City a("a");
			Town b("b");
			City c("c");
			Town d("d");
			Town e("e");
			City f("f");
			Town g("g");
			City x("x"); //disconnected
			vector<Place> testVertexes = { a, b, c, d, e, f, g, x };
			Edge<Place> e01 = Edge<Place>(a, b, 1);
			Edge<Place> e02 = Edge<Place>(a, b, 2);
			Edge<Place> e03 = Edge<Place>(a, d, 3);
			Edge<Place> e04 = Edge<Place>(d, c, 4);
			Edge<Place> e05 = Edge<Place>(b, c, 5);
			Edge<Place> e06 = Edge<Place>(b, e, 7);
			Edge<Place> e07 = Edge<Place>(c, e, 2);
			Edge<Place> e08 = Edge<Place>(c, g, 2);
			Edge<Place> e09 = Edge<Place>(b, f, 42);
			Edge<Place> e10 = Edge<Place>(g, f, 6);
			vector<Edge<Place>> testEdges = { e01, e02, e03, e04, e05, e06, e07, e08, e09 , e10};
			vector<Edge<Place>> dijkstraEdges = {e01, e05, e03, e06, e10, e08};
 			for (auto it = testEdges.begin(); it != testEdges.end(); ++it) {
				_graph.Add(*it);
			}
			DijkstraAlgorithm<Place, Edge> dijkstraAlgorithm(&_graph, a);
			vector<Edge<Place>> dijOut = dijkstraAlgorithm.GetMinimumPaths();
			Assert::IsTrue(dijOut.size() == dijkstraEdges.size());
			Assert::IsTrue(equal(dijkstraEdges.begin(), dijkstraEdges.begin() + dijkstraEdges.size(), dijOut.begin()));
		}

		TEST_METHOD(Pqueue)
		{
			PriorityQueue<string> pqs;
			string a = "a";
			string b = "b";
			string c = "c";
			string d = "d";
			string z = "z";

			// enqueue - contains
			Assert::IsFalse(pqs.Contains(b));
			pqs.Enqueue(2, b);
			Assert::IsTrue(pqs.Contains(b));
			pqs.Enqueue(1, a);
			Assert::IsTrue(pqs.Contains(a));
			pqs.Enqueue(4, d);
			Assert::IsTrue(pqs.Contains(d));
			pqs.Enqueue(3, c);
			Assert::IsTrue(pqs.Contains(c));

			// top - change priority
			pqs.Enqueue(0, z);
			Assert::IsTrue(pqs.Contains(z));
			Assert::IsTrue(*(pqs.Top()) == z);
			pqs.SafeChangePriority(0, 42, z);

			Assert::IsTrue(*(pqs.Dequeue()) == a);
			Assert::IsTrue(*(pqs.Dequeue()) == b);
			Assert::IsTrue(*(pqs.Dequeue()) == c);
			Assert::IsTrue(*(pqs.Dequeue()) == d);
			Assert::IsTrue(*(pqs.Dequeue()) == z);
			Assert::IsTrue(pqs.Dequeue() == nullptr);
		}
			
	};

};