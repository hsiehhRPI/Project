public String findPath(String part1, String part2) {
		String res = "";
		//First we should check whether the part is in the graph
		if (!this.graph.getVertSet().contains(part1)&&!this.graph.getVertSet().contains(part2)) {
			//Both not in graph
			if (part1.equals(part2)) {
				res = "unknown part " + part1 + "\n";
				return res;
			}
			res = "unknown part " + part1 + "\nunknown part " + part2 + "\n";
			return res;
		}
		else if (!this.graph.getVertSet().contains(part1)) {
			//Part 1 is not in graph
			res = "unknown part " + part1 + "\n";
			return res;
		}
		else if (!this.graph.getVertSet().contains(part2)) {
			//Part 2 is not in graph
			res = "unknown part " + part2 + "\n";
			return res;
		}
		//Check if two inputs are the same
		res = "path from "+ part1 +" to "+ part2 +":\n";

		if (part1.equals(part2)) {
			String tmp = res.concat("total cost: 0.000");
			res = tmp;
			return res;
		} 
		//After checking the special cases, do the actual algorithm
		//This really does not work with my structure, I am struggling to sort the priority by weight
		//Set up
		Map<String, Double> pathWeights = new HashMap<String, Double>();
		ArrayList<String> queue = new ArrayList<String>();			//Will hold the key to the least 
		Map<String, ArrayList<String>> pathHold = new HashMap<String, ArrayList<String>>();
		Set<String> done = new HashSet<String>();
		ArrayList<String> start = new ArrayList<String>();
		start.add(part1);
		start.add("0.000");
		pathHold.put(part1, start);
		queue.add("0.000|".concat(part1));				///Work around, since we need to sort by weight, append weight to the start of the string
		pathWeights.put(part1, 0.0000);
		while (!queue.isEmpty()) {
			//Pop the first out of the queue
			Collections.sort(queue);
			String cur = queue.get(0);
			int sepIdx = cur.indexOf('|');
			String current = cur.substring(sepIdx+1, cur.length());
			queue.remove(0);
			ArrayList<String> curPath = pathHold.get(current);
			if (current.equals(part2)) {
				//If we find the target, format the answer
				String hold;
				String tmp;
				for (int n = 0; n < curPath.size()-2; n+=2) {
					hold = curPath.get(n)+" to "+ curPath.get(n+2)+" with weight "+String.format("%.3f\n", pathWeights.get(curPath.get(n+2)));
					tmp = res.concat(hold);
					res = tmp;
				}
				tmp = res.concat(String.format("total cost: %.3f\n", pathWeights.get(current)));
				res = tmp;
				return res;
			}
			if (done.contains(current)) {
				//Already visited, not the destination we want
				pathWeights.remove(current);
				continue;
			}
			for (Iterator<String> btr = this.graph.sortNeighbors(current); btr.hasNext(); ) {
				String weightEdge = btr.next();
				//Peel off the edge weight and the name of the destination
				int idxOfSep = weightEdge.indexOf('|');
				String weightInStr = weightEdge.substring(0, idxOfSep);
				String dest = weightEdge.substring(idxOfSep+1, weightEdge.length());
				Double weight = Double.parseDouble(weightInStr);
				if (!done.contains(dest)) {
					ArrayList<String> nPath = new ArrayList<String>(curPath);
					nPath.add(dest);
					Double nWeight = pathWeights.get(current);
					nWeight += weight;
					if (weightInStr.length() > 5) {
						nPath.add(weightInStr.substring(0, 5));
					}
					else {
						nPath.add(weightInStr);
					}
					queue.add(weightInStr+"|"+dest);
					//This is where I had to do a work around, we are going to sort the name of nodes by total weight instead
					pathWeights.put(dest, nWeight);
					pathHold.put(dest, nPath);
				}
			}
			done.add(current);
		}
		String hold = res.concat("no path found\n");
		res = hold;
		return res;