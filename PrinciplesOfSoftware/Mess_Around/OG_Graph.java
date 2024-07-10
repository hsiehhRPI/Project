package hw4;

import java.util.*;
import java.awt.datatransfer.SystemFlavorMap;
import java.lang.Iterable;
import java.lang.reflect.Array;

/** <b>Graph</b> represents an <b>immutable</b> directed graph(adjacency list representation) 
 * (or undirected graph if you implemented edges in reversed pairs).
 * We represent vertex in a graph as String ArrayLists that follows this structure:
 * - Index 0: Name of the vertex(these must be unique)
 * - Odd index: Name of the destination vertex
 * - Even index not 0: Label of the edge start at index 0 to destination specified at current index-1
 * Some rules regarding the graph implementation:
 * - There only exist one edge that connects one source to destination
 * (There will not exist two edges go from vertex A to E)
 * - Label name of edges can be the same, but cannot both start at the same vertex
 * (AE and AB cannot both be named "cat", but BE and AE can both be named "dog")
 * - An edge CAN have same source and destination
 * - Graphs are isomorphic if vertex and edges are the same, but different label names exist
 * - Graphs are equivalent if all attributes: vertex, edge, and labels of edges are the same.
*/

public class Graph<T,S> {
	//Okay there lies a problem with the current implementation(before making it into genetics)
	//My graph can only accommodate for storing nodes and edges as the same datatype, 
	//so we will have a lot of adaptation to adjust to solve the problem of different datatype
	//Solution to this problem: the 2D ArrayList now only stores the vertices, we will have a map that maps the source vertices to the name of the edge
	//To determine which is the correct edge, we will use the destination node index -1 to find the correct edge name

	private final Map<T,ArrayList<S>> vertMap;			//Maps source vertices to various edge names
	private final Map<T,ArrayList<T>> Graph;		//First index of each embedded vertex is the source, follow by a series of destination
	private final Set<T> vertSet;						//Set of all vertices
	private final int nVertex;							//Total number of vertices
	private final int nEdge;							//Total number of edges
	private ArrayList<S> edgeLabels;
	private ArrayList<T> vertOfEdges;
	
	//  A Graph r is empty when the 2D ArrayList does not contain any elements.
    //	If the Graph contains vertices, the name of the vertex will be at index 0 of the nested ArrayList
	//	If the vertex has edges that start from the current vertex to another vertex, 
	//		then it follows the format: 
	//		- Index 0: name of vertex
	//		- Odd indices: name of destination vertex	(by order these edges are formed
	//		- Even indices not 0: name of the edge label
	
    // Representation invariant for every Graph g:
    //   g!=null && 
    //   for (int n = 0; n < g.size(); n++) {
	//		g.get(n) != null
	//	 }
	//	  && a set containing all vertices = g.size()
	//	  && only one edge between a source to destination
	//(ie there should be max one edge going from vertex a to e, it is okay to have another edge e to a)
	//	  && all edges must have source, destination, and edge label
	//
    //   The above suggests
    //     * All Graph's ArrayLists should not be null
    //     * There should be no repeating vertex names
	//	   * There exists one edge between the same source to destination
	//	   * All edges must have source and destination
    // (A representation invariant tells us something that is true for all
    // valid instances of a Graph)
	
	
	
	//Creators
	//Javadoc comments
	/**
	 * @param T, type of the vertices. S, type of the edges.
	 * @return new Graph with no vertex or edge(empty graph)
	 * @throw none
	 * */
	//Psoft notation
	/**
	 * @param T, type of the vertices. S, type of the edges.
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns new Graph with no vertex or edge(empty graph)*/
	public Graph() {
		//Set up an empty array, all fields initialized to empty
		this.Graph = new HashMap<T, ArrayList<T>>();
		this.vertMap = new HashMap<T, ArrayList<S>>(); 
		this.nEdge = 0;
		this.nVertex = 0;
		this.vertSet = new HashSet<T>();
		this.edgeLabels = new ArrayList<S>();
		this.vertOfEdges = new ArrayList<T>();
		//checkRep();	//Did this on my computer, comment it out for submitty
		//throw new RuntimeException("Graph constructor is not implemented");
	}
	//Javadoc comments
	/**
	* @param T, type of the vertices. S, type of the edges.
	* @param vertex type T, name of the vertex to create
	* @return new Graph with one vertex with name specified
	* @throw none
	* */
	//Psoft notation
	/**
	* @param T, type of the vertices. S, type of the edges.
	* @param vertex	type T, name of the vertex
	* @requires none
	* @modifies none
	* @throws none
	* @effects none
	* @returns new Graph with one vertex with name specified*/
	public Graph(T vertex) {
		//Creates graph of one vertex, add vertex in to vertSet, vertices.
		this.Graph = new HashMap<T, ArrayList<T>>();
		this.vertMap = new HashMap<T, ArrayList<S>>();
		this.vertOfEdges = new ArrayList<T>();
		ArrayList<T> tmp = new ArrayList<T>();
		tmp.add(vertex);
		this.Graph.put(vertex, tmp);
		this.nEdge = 0;
		this.vertSet = new HashSet<T>();
		this.vertSet.add(vertex);
		this.nVertex = vertSet.size();
		this.edgeLabels = new ArrayList<S>();
		//checkRep();

		//throw new RuntimeException("Graph constructor is not implemented");
	}	
	//Javadoc comments
		/**
		 * @param vertices T Arraylist contain names of all vertices
		 * @param sourceDest T ArrayList contain names of vertices such that all even indices are sources, odd indices are destination
		 * @param edges S Arraylist that at 0 indices corresponds to indices 0 and 1 of sourceDest ArrayList
		 * source, destination, label, and so on... 
		 * @return new Graph with specified vertices and edges.
		 * @throw none
		 * */
		//Psoft notation
		/**
		 * @param vertices T ArrayList contain names of all vertices
		 * @param sourceDest T ArrayList contain names of vertices such that all even indices are sources, odd indices are destination
		 * @param edges S Arraylist that at 0 indices corresponds to indices 0 and 1 of sourceDest ArrayList
		 * source, destination, label, and so on... 
		 * @requires edges.size()%3 == 0
		 * @modifies none
		 * @throws none
		 * @effects none
		 * @returns new Graph with specified vertices and edges.*/
	public Graph(ArrayList<T> vertices, ArrayList<T> sourceDest, ArrayList<S> edges) {
		this.Graph = new HashMap<T, ArrayList<T>>();
		this.edgeLabels = new ArrayList<S>();
		this.vertOfEdges = sourceDest;
		Set<T> track = new LinkedHashSet<T>();
		//Initialize the vertices
		for (int n = 0; n < vertices.size(); n++) {
			//Initialize the vertices first
			//Check if the graph already have the vertex
			if (!track.contains(vertices.get(n))) {
				//If not
				track.add(vertices.get(n));
				ArrayList<T> tmp = new ArrayList<T>();
				this.Graph.put(vertices.get(n), tmp);
			}			
		}
		this.nVertex = track.size();
		this.vertSet = track;
		this.vertMap = new HashMap<T, ArrayList<S>>();
		int count = 0;
		//Initialize the edges
		for (int v = 0; v < sourceDest.size()-1; v+=2) {
			if (this.Graph.containsKey(sourceDest.get(v))&& this.Graph.containsKey(sourceDest.get(v+1))) {
				this.Graph.get(sourceDest.get(v)).add(sourceDest.get(v+1));			//Add destination vertex to the source vertex ArrayList
				this.edgeLabels.add(edges.get(count));
				//Both source and destination are in the graph, edge can form
				//Check if source is already in the HashMap
				if (this.vertMap.containsKey(sourceDest.get(v))) {
					this.vertMap.get(sourceDest.get(v)).add(edges.get(count));
				}
				else {
					ArrayList<S> hold = new ArrayList<S>();
					hold.add(edges.get(count));
					this.vertMap.put(sourceDest.get(v), hold);
				}
				count++;
			}
		}
		this.nEdge = count;
		//checkRep();

		//throw new RuntimeException("Graph constructor is not implemented");
	}
	
	/*Newly implemented constructor for hw5*/
	//Javadoc comments
			/**
			 * @param vertex Set<String> that contain names of vertices to create
			 * @param edgesDest  Map<String, Set<String>> where the key is the label and Set<String> contains the nodes
			 * @return new Graph with specified vertices and edges.
			 * @throw none
			 * */
			//Psoft notation
			/**
			 * @param vertex Set<String> that contain names of vertices to create
			 * @param edgesDest  Map<String, Set<String>> where the key is the label and Set<String> contains the nodes
			 * @requires none
			 * @modifies none
			 * @throws none
			 * @effects none
			 * @returns new Graph with specified vertices and edges.*/
	public Graph(Set<T> vertex, Map<S, Set<T>>edgeDest) {
		this.vertSet = vertex;
		this.nVertex = vertex.size();
		this.vertOfEdges = new ArrayList<T>();
		this.Graph = new HashMap<T, ArrayList<T>>();
		//Initialize all vertices
		for (Iterator<T> itr = vertex.iterator(); itr.hasNext();) {
			ArrayList<T> vert = new ArrayList<T>();
			this.Graph.put(itr.next(),vert);
		}
		//Initializing the edges
		//Idea: loop through each courses, find the professors that's also in the same set and use the course name as label
		T source;
		T dest;
		S label;
		int count = 0;
		this.vertMap = new HashMap<T, ArrayList<S>>();
		for (Map.Entry<S, Set<T>> me : edgeDest.entrySet()) {
			//Looping through the courses
			label = me.getKey();		//Edge label are the name of the courses
			Set<T> destination = me.getValue();		//The professors that teach the course
			ArrayList<T> destArr = new ArrayList<T>(destination);
			//Looping through the professors
			for (int x = 0; x < destArr.size(); x++) {
				for (int v = 0; v < destArr.size(); v++) {
					//Make sure to not self loop here
					if (v!=x) {	
						source = destArr.get(x);
						dest = destArr.get(v);
						this.vertOfEdges.add(source);
						this.vertOfEdges.add(dest);
						//Search for target vertex in the vertex map
						if (this.Graph.containsKey(source)&& this.Graph.containsKey(dest)) {
							this.Graph.get(source).add(dest);
							if (this.vertMap.containsKey(source)) {
								this.vertMap.get(source).add(label);
							}
							else {
								ArrayList<S> edgeList = new ArrayList<S>();
								edgeList.add(label);
								this.vertMap.put(source, edgeList);
							}
							count++;
						}
					}
				}
			}
		}
		this.nEdge = count;
		//checkRep();			//Commented out because the large graphs takes a while to run
	}
	
	/*Newly added function for hw6*/
	//Javadoc comments
	/**
	 * @param vertex, set of vertices type T
	 * @param graph, set of vertices(type T) map to arrayList of destination vertices(type T)
	 * @param vertMap, set of vertices(type T) map to ArrayList of edge labels(type S)
	 * @param VOE, ArrayList<T> where even indices are sources, odd are destination
	 * @param weights, such that weights[0] correspond to VOE[0][1], weight[1] = VOE[2][3] and so on 	 
	 * @returns new Graph with all fields initialized by the given information.
	 * @throw none
	 * */
	//Psoft notation
	/**
	 * @param vertex, set of vertices type T
	 * @param graph, set of vertices(type T) map to arrayList of destination vertices(type T)
	 * @param vertMap, set of vertices(type T) map to ArrayList of edge labels(type S)
	 * @param VOE, ArrayList<T> where even indices are sources, odd are destination
	 * @param weights, such that weights[0] correspond to VOE[0][1], weight[1] = VOE[2][3] and so on 
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns new Graph with all fields initialized by the given information.*/
	public Graph(Set<T> vertex,  Map<T,ArrayList<T>> graph, Map<T, ArrayList<S>>vertMap, ArrayList<T>VOE, ArrayList<S> weights) {
		this.Graph = graph;
		this.vertMap = vertMap;
		this.vertOfEdges = VOE;
		this.nEdge = weights.size();
		this.vertSet = vertex;
		this.nVertex = vertSet.size();
		this.edgeLabels = weights;
	}	
	
	//Observers
	//Javadoc comments
	/**
	 * @param none
	 * @return total number of vertices in the graph
	 * @throw none
	 * */
	//Psoft notation
	/**
	 * @param none
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns total number of vertices in the graph*/
	public int getTotalVertices() {
		//Return the number of vertices in graph
		return this.nVertex;
		//throw new RuntimeException("getTotalVertices is not implemented");
	}
	//Javadoc comments
	/**
	 * @param none
	 * @return total number of edges in the graph
	 * @throw none
	 * */
	//Psoft notation
	/**
	 * @param none
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns total number of edges in the graph*/
	public int getTotalEdges() {
		//Return the number of edges in graph
		return this.nEdge;
		//throw new RuntimeException("getTotalEdges is not implemented");
	}
	
	//This is added later, when GraphWrapper is implementing
	public Set<T> getVertSet() {
		return this.vertSet;
	}
	
	//Javadoc comments
	/**
	 * @param vertex 	T that is name of a vertex
	 * @param destination	ArrayList<T> that can be use to hold info of the destination
	 * @returns A map where destination nodes are keys map to edge labels
	 * @throw none
	 * */
	//Psoft notation
	/**
	 * @param vertex 	T that is name of a vertex
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns A map where destination nodes are keys map to edge labels*/
	//I changed this function for hw5
	public HashMap<T,S> getVertex(T vertex) {
		//If Vertex is not in the graph, return
		HashMap<T,S> destEdgePair = new HashMap<T,S>();
		if (this.vertSet.contains(vertex)==false) {
			return destEdgePair;
		}
		//Return the array representing that 
		//Make a copy, we don't let the client mess with our immutable object
		//How to copy array:
		//https://www.baeldung.com/java-copy-list-to-another#:~:text=A%20simple%20way%20to%20copy,element%20will%20affect%20both%20lists.
		if (this.Graph.containsKey(vertex)&&this.vertMap.containsKey(vertex)) {
			ArrayList<T> tmp = this.Graph.get(vertex);
			for (int n = 0; n < tmp.size(); n++) {
				destEdgePair.put(tmp.get(n), this.vertMap.get(vertex).get(n));
			}
		}
		return destEdgePair;
	}
	//Javadoc comments
		/**
		* @param source 	T that is name of a vertex
		 * @param label		S that is the name of the edge
		 * @returns result type T which is the name of the destination vertex
		 * @throw none
		 * */
		//Psoft notation
		/**
		 * @param source 	T that is name of a vertex
		 * @param label		S that is the name of the edge
		 * @requires none
		 * @modifies none
		 * @throws none
		 * @effects none
		 * @returns result type T which is the name of the destination vertex*/
	public T getDest(T source, S label) {
		//If the source is not in the graph, such edge cannot exist
		T result = null;
		if (this.vertSet.contains(source)==false) {
			return result;
		}
		ArrayList<S> tmp = this.vertMap.get(source);
		//There is no edge connected to the source specified
		if (tmp==null) {
			return result;
		}
		T dest;
		for (int n = 0; n < tmp.size(); n++) {
			if (tmp.get(n)==label) {
				dest =  this.Graph.get(source).get(n);
				return dest;
			}
		}
		return result;
		//If the destination just does not exist
		//throw new RuntimeException("getEdge is not implemented");
	}
	//Javadoc comments
		/**
		 * @param source	T that is name of the source vertex
		 * @param dest		T that is name of the destination vertex
		 * @return S that is name of the edge from source to dest
		 * @throw none
		 * */
		//Psoft notation
		/**
		 * @param source	T that is name of the source vertex
		 * @param dest		T that is name of the destination vertex
		 * @requires none
		 * @modifies none
		 * @throws none
		 * @effects none
		 * @returns S that is the name of the edge from source to dest*/
	public S getEdgeLabel(T source, T dest) {
		S res = null;
		//If source/dest is not in graph, return empty string
		if (!this.vertMap.containsKey(source)) {
			return res;
		}
		ArrayList<T> tmp = this.Graph.get(source);
		for (int n = 0; n < tmp.size(); n++) {
			if (tmp.get(n)==dest) {
				res = this.vertMap.get(source).get(n);
				return res;
			}
		}
		return res;
		//throw new RuntimeException("Graph is not implemented");
	}
	
	public ArrayList<T> getVertexOfEdges() {
		return this.vertOfEdges;
	}
	public ArrayList<S> getAllEdgeLabels() {
		return this.edgeLabels;
	}
	//Producers
	//Javadoc comments
	/**
	* @param name	String that is name of a vertex to add to graph
	* @return if name is not a vertex in graph, new graph with new vertex added is returned,
	* otherwise, original graph is returned
	* @throw none*/
	//Psoft notation
	/**
	* @param vertex 	String that is name of a vertex
	* @requires none
	* @modifies none
	* @throws none
	* @effects none
	* @returns If name is not a vertex in graph, new graph with new vertex added is returned,
	* otherwise, original graph is returned*/
	public Graph<T,S> addVertex(T name) {
		//If the vertex of same name already existed, return original object
		if (this.vertSet.contains(name)) {
			//Convert Set to ArrayList: https://stackoverflow.com/questions/5982447/how-to-convert-setstring-to-string
			ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
			return new Graph<T,S>(ogVerts, this.getVertexOfEdges(), this.getAllEdgeLabels());
		}
		//If not present in graph, add such vertex to graph
		ArrayList<T> totalVert = new ArrayList<T>(this.vertSet);
		totalVert.add(name);
		//Make a new graph with the vertex added
		return new Graph<T,S>(totalVert, this.getVertexOfEdges(), this.getAllEdgeLabels());	
		//throw new RuntimeException("addVertex is not implemented");
	}
	//Javadoc comments 
	/**
	 * @param source	String that is name of a source vertex
	 * @param dest		String that is name of a dest vertex
	 * @para  label		String that is name of the edge to be added
	 * @returns if(source/dest is not in the graph or if source to dest edge already exist)
	 * return original graph, otherwise new graph with edge added will be returned 
	 * @throw none*/
	//psoft notation
	/**
	 * @param source	String that is name of a source vertex
	 * @param dest		String that is name of a dest vertex
	 * @para  label		String that is name of the edge to be added
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns if(source/dest is not in the graph or if source to dest edge already exist) 
	 * return original graph , otherwise new graph with edge added will be returned*/
	public Graph<T,S> addEdge (T source, T dest, S label) {
		if (this.vertSet.size() < 2) {
			//We need at least two vertex to form an edge
			//Convert Set to ArrayList: https://stackoverflow.com/questions/5982447/how-to-convert-setstring-to-string
			ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
			return new Graph<T,S>(ogVerts, this.getVertexOfEdges(), this.edgeLabels);
		}
		if (this.vertSet.contains(source)==false || this.vertSet.contains(dest) == false) {
			//If one of the vertices was not in the graph, edge cannot be form
			ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
			return new Graph<T,S>(ogVerts, this.getVertexOfEdges(), this.edgeLabels);
		}
		//Add new edges
		ArrayList<T> newEdge = new ArrayList<T>(this.vertOfEdges);
		newEdge.add(source);
		newEdge.add(dest);
		ArrayList<T> vert = new ArrayList<T>(vertSet);
		//return graph with new edge added
		ArrayList<S> ne = new ArrayList<S>(this.edgeLabels);
		ne.add(label);
		return new Graph<T,S>(vert, newEdge, ne);
		//throw new RuntimeException("addEdge is not implemented");
	}
	//Javadoc comment
	/**
	 * @param name	String that is name of a vertex to remove
	 * @returns if vertex of specified name not in graph,
	 * return original graph, otherwise new graph with vertex removed will be returned 
	 * @throw none*/
	//psoft notation
	/**
	 * @param name	String that is name of a vertex to remove
	 * @requires none
	 * @modifies none
	 * @throws none
	 * @effects none
	 * @returns if vertex of specified name not in graph,
	 * return original graph, otherwise new graph with vertex removed will be returned*/
	
	public Graph<T,S> removeVertex(T name) {
		if (vertSet.contains(name)==false) {
			//If the graph already did not have that vertex, just return it
			//Convert Set to ArrayList: https://stackoverflow.com/questions/5982447/how-to-convert-setstring-to-string
			ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
			return new Graph<T,S>(ogVerts, this.vertOfEdges, this.edgeLabels);
		}
		//Set up a new graph where the vertex is removed
		ArrayList<T> nVerts = new ArrayList<T>();
		for (Iterator<T> itr = this.vertSet.iterator(); itr.hasNext();) {
			nVerts.add(itr.next());
		}
		nVerts.remove(name);
		ArrayList<S> nEdges = new ArrayList<S>();
		ArrayList<T> nEdgeDest = new ArrayList<T>();
		
		for (int n = 0; n < nVerts.size(); n++) {
			if (!nVerts.get(n).equals(name)) {
				ArrayList<T> tmp = this.Graph.get(nVerts.get(n));
				for (int p = 0; p < tmp.size(); p++) {
					if (!tmp.get(p).equals(name)) {
						nEdgeDest.add(nVerts.get(n));
						nEdgeDest.add(tmp.get(p));
						nEdges.add(this.vertMap.get(nVerts.get(n)).get(p));
					}
				}
			}
		}
		//Make a graph with the necessary info
		return new Graph<T,S>(nVerts, nEdgeDest, nEdges);
		//throw new RuntimeException("removeVertex is not implemented");
	}
	//Javadoc comment
		/**
		 * @param source	String that is name of a source vertex
		 * @param dest 		String that is name of a end vertex
		 * @returns if specified edge not in graph,
		 * return original graph, otherwise new graph with edge removed will be returned 
		 * @throw none*/
		//psoft notation
		/**
		 * @param source	String that is name of a source vertex
		 * @param dest 		String that is name of a end vertex
		 * @requires none
		 * @modifies none
		 * @throws none
		 * @effects none
		 * @returns if vertex of specified name not in graph,
		 * return original graph, otherwise new graph with edge removed will be returned*/
		public Graph<T,S> removeEdge(T source, T dest, S label) {
			if (this.vertSet.size() < 2) {
				//If a graph has less than 2 vertices, it cannot have an edge
				//Convert Set to ArrayList: https://stackoverflow.com/questions/5982447/how-to-convert-setstring-to-string
				ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
				return new Graph<T,S>(ogVerts, this.vertOfEdges, this.edgeLabels);
			}
			else if (this.Graph.keySet().contains(source)==false || this.vertSet.contains(dest)==false||this.vertMap.containsKey(source)==false) {
				//If one of the endpoints of the edge is not in graph, or source exists in graph but has no connections
				ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
				return new Graph<T,S>(ogVerts, this.vertOfEdges, this.edgeLabels);
			} 
			else if (this.vertMap.get(source).indexOf(label)!=this.Graph.get(source).indexOf(dest)) {
				//If the name of the label is not correct
				ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
				return new Graph<T,S>(ogVerts, this.vertOfEdges, this.edgeLabels);
			}
			else if (!this.vertMap.get(source).contains(label)||!this.Graph.get(source).contains(dest)) {
				ArrayList<T> ogVerts = new ArrayList<T>(this.vertSet);
				return new Graph<T,S>(ogVerts, this.vertOfEdges, this.edgeLabels);
			}
			//Set up a new Graph with target edge removed
			ArrayList<T> nVert = new ArrayList<T>(this.vertSet);
			ArrayList<T> nVOE = new ArrayList<T>();
			ArrayList<S> newEdge = new ArrayList<S>();
			for (int n = 0; n < nVert.size(); n++) {
				ArrayList<T> tmp = this.Graph.get(nVert.get(n));
				ArrayList<S> edgeL = this.vertMap.get(nVert.get(n));
				for (int v = 0; v < tmp.size(); v++) {
					if (!(tmp.get(v).equals(dest)&&nVert.get(n).equals(source))) {
						nVOE.add(nVert.get(n));
						nVOE.add(tmp.get(v));
						newEdge.add(edgeL.get(v));
					}
				}
			}
			
			return new Graph<T,S>(nVert, nVOE, newEdge);
			//throw new RuntimeException("removeEdge is not implemented");
		}

		/*Copied from GraphWrapper*/
		public Iterator<String> listNodes() {
			//I have looked up some resources to help me with this problem
			//How to sort a set in Java: https://www.baeldung.com/java-sort-hashset
			Set<T> allVerts = this.getVertSet();
			//Got to cast everything to string
			ArrayList<String> tmp = new ArrayList<String>();
			for (Iterator<T> itr = allVerts.iterator(); itr.hasNext();) {
				tmp.add((itr.next()).toString());
			}
			Collections.sort(tmp);
			Iterator<String> nodeItr = tmp.iterator();
			return nodeItr;
			
		}
		
		/*Copied from GraphWrapper*/
		public Iterator<String> listChildren(T parentNode) {
			ArrayList<T> neighbors = this.Graph.get(parentNode);
			ArrayList<S> edgeLabels = this.vertMap.get(parentNode);
			//If we have an empty Graph or a disconnected vertex, we cannot have edges
			String dest = "";
			String label;
			ArrayList<String> replaced = new ArrayList<String>();
			Iterator<String> itr = replaced.iterator();
			if (neighbors.size()==0||edgeLabels.size()==0) {
				return itr;
			}
			for (int n = 0; n < neighbors.size(); n++) {
				dest = (neighbors.get(n)).toString();
				label = (edgeLabels.get(n)).toString();
				String tmp = dest.concat("(").concat(label).concat(")");
				replaced.add(tmp);				
			}
			Collections.sort(replaced);
			itr = replaced.iterator();
			return itr;
		}
		
		public String formString() {
			String res = "";
			ArrayList<String> forCast = new ArrayList<String>();
			for (Iterator<T> itr = this.vertSet.iterator(); itr.hasNext();) {
				T hold = itr.next();
				ArrayList<T> dests = this.Graph.get(hold);
				ArrayList<S> edges = this.vertMap.get(hold);
				if (dests == null) {
					dests = new ArrayList<T>();
				}
				if (edges == null) {
					edges = new ArrayList<S>();
				}
				forCast.add(hold.toString());
				if (dests.size()==edges.size()&&dests.size()>0) {
					for (int n = 0; n < dests.size(); n++) {
						forCast.add((dests.get(n)).toString());
						forCast.add((edges.get(n)).toString());
					}
				}
			}
			res = String.join("|", forCast);
			return res;
		}
}