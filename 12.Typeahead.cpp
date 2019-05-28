/*
12.Typeahead
Implement typeahead. Given a string and a dictionary, return all words that contains the string as a substring. The dictionary will give at the initialize method and wont be changed. The method to find all words with given substring would be called multiple times.
 Example
Given dictionary = {"Jason Zhang", "James Yu", "Bob Zhang", "Larry Shi"}
search "Zhang", return ["Jason Zhang", "Bob Zhang"].
search "James", return ["James Yu"].
solution:
There are two ways to do this, one is the Inverted Index and the other is the Trie Tree.
The difference between the two approaches is how to store keywords.
Use the more efficient Trie Tree here.
For how to implement Trie Tree, please refer to Implement Trie and Trie Service.
At the time of storage, each Trie Node saves the hot words of this node and all the child nodes below, so that it can be quickly returned without traversing.
It should be noted that when inserting new keywords, each word should be inserted once as the starting word from the beginning to the end of each character. This ensures that the user can quickly find a list of popular words when they start typing from a character in the middle of a word.
*/



public class Typeahead {
    private class TreeNode {
        Set<String> tops;
        Map<Character, TreeNode> neighbors;
        public  TreeNode () {
            tops = new HashSet<String>();
            neighbors = new HashMap<Character, TreeNode>();
        }
    }
    
    TreeNode root;
    
    // @param dict A dictionary of words dict
    public Typeahead(Set<String> dict) {
        root = buildTree(dict);
    }

    // @param str: a string
    // @return a list of words
    public List<String> search(String str) {
        TreeNode next = root;
        
        for (char c : str.toCharArray()) {
            if (!next.neighbors.containsKey(c)) {
                return new ArrayList<String>();
            }
            next = next.neighbors.get(c);
        }
        
        return new ArrayList<String>(next.tops);
    }
    
    private TreeNode buildTree(Set<String> dict) {
        TreeNode _root = new TreeNode();
        
        for (String word : dict) {
            for (int i = 0; i < word.length(); i++) {
                TreeNode next = _root;
                String subWord = word.substring(i);
                for (char c : subWord.toCharArray()) {
                    if (!next.neighbors.containsKey(c)) {
                        next.neighbors.put(c, new TreeNode());
                    }
                    
                    next = next.neighbors.get(c);
                    next.tops.add(word);
                }
            }
        }
        
        return _root;
    }
}
