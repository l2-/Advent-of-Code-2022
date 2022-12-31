using System.Text.Json;
namespace MyProject;

abstract class Node
{
    public abstract int Compare(Node other);
}

class Leaf : Node
{
    public int value { get; set; } = 0;

    public override int Compare(Node other)
    { 
        if (other is Branch)
        {
            Branch otherb = (Branch)other;
            Branch thisb = new Branch();
            thisb.children.Add(this);
            return thisb.Compare(otherb);
        }
        else
        {
            Leaf leaf = (Leaf)other;
            return value.CompareTo(leaf.value);
        }
        throw new Exception("Not leaf or branch");
    }

    public override string ToString()
    {
        return value.ToString();
    }
}

class Branch : Node, IComparable<Branch>
{
    public List<Node> children { get; set; } = new List<Node>();

    public override int Compare(Node other)
    {
        if (other is Branch)
        {
            Branch otherb = (Branch)other;

            if (children.Count == 0)
            {
                return children.Count.CompareTo(otherb.children.Count);
            }

            int i = 0;
            int cmp = 0;
            for (; i < children.Count - 1; i++)
            {
                if (i >= otherb.children.Count)
                {
                    return 1;
                }
                cmp = children[i].Compare(otherb.children[i]);
                if (cmp != 0) return cmp;
            }
            if (i >= otherb.children.Count)
            {
                return 1;
            }
            cmp = children[i].Compare(otherb.children[i]);
            if (cmp < 1 && children.Count < otherb.children.Count)
            {
                return -1;
            }
            return cmp;
        }
        else
        {
            if (children.Count == 0)
            {
                return -1;
            }

            Branch otherb = new Branch();
            otherb.children.Add(other);
            return Compare(otherb);
        }
        throw new Exception("Not leaf or branch");
    }

    public int CompareTo(Branch? other)
    {
        if (other == null) throw new Exception("Wont happen :)");
        return Compare(other);
    }

    public override string ToString()
    {
        if (children.Count == 0) return "[]";
        string res = "[";
        foreach (Node node in children)
        {
            res += node.ToString() + ",";
        }
        var arr = res.ToCharArray();
        arr[res.Length - 1] = ']';
        return new string(arr);
    }
}

class Comparison
{
    public Node? node1 = null;
    public Node? node2 = null;
    public int Compare()
    {
        return node1.Compare(node2);
    }

    public override string ToString()
    {
        return string.Format("Comparing {0} {1}", node1.ToString(), node2.ToString());
    }
}

class Program
{
    static void RecursiveParse(JsonElement jsonElement, ref Branch node)
    {
        if (jsonElement.ValueKind == JsonValueKind.Array)
        {
            Branch branch = new Branch();
            node.children.Add(branch);
            foreach (var element in jsonElement.EnumerateArray())
            {
                RecursiveParse(element, ref branch);
            }
        }
        else if (jsonElement.ValueKind == JsonValueKind.Number)
        {
            Leaf leaf = new Leaf() { value = jsonElement.GetInt32() };
            node.children.Add(leaf);
        }
        else
        {
            throw new Exception("Not a number nor array");
        }
    }

    static void Main(string[] args)
    {
        string[] lines = File.ReadAllLines("day13.txt");

        List<Comparison> comparisons = new List<Comparison>();
        List<Branch> branches = new List<Branch>();
        comparisons.Add(new Comparison());
        foreach (string line in lines)
        {
            if (line.Equals(""))
            {
                continue;
            }
            var doc = JsonDocument.Parse(line);
            Branch rootNode = new Branch();
            RecursiveParse(doc.RootElement, ref rootNode);
            rootNode = rootNode.children[0] as Branch;
            branches.Add(rootNode);

            Comparison comparison = comparisons.Last<Comparison>();
            if (comparison.node1 == null) comparison.node1 = rootNode;
            else if (comparison.node2 == null) comparison.node2 = rootNode;
            else { comparison = new Comparison(); comparison.node1 = rootNode; comparisons.Add(comparison); }
        }
        Branch branch1 = new Branch() { children = new List<Node>() { new Branch() { children = new List<Node>() { new Leaf() { value = 2 } } } } };
        Branch branch2 = new Branch() { children = new List<Node>() { new Branch() { children = new List<Node>() { new Leaf() { value = 6 } } } } };
        branches.Add(branch1);
        branches.Add(branch2);

        List<int> correctPacketIndices = new List<int>();
        int index = 1;
        foreach (var comparison in comparisons)
        {
            bool cmp = false;
            if (cmp = (comparison.Compare() < 0))
            {
                correctPacketIndices.Add(index);
            }
            //Console.WriteLine("{0} {1} {2}", index, comparison.ToString(), cmp);
            index++;
        }

        Console.WriteLine("Sum of corrent indices {0}", correctPacketIndices.Sum());

        branches.Sort();
        index = 1;
        int index2 = 0;
        int index6 = 0;
        foreach (var branch in branches)
        {
            if (branch.Equals(branch1)) index2 = index;
            if (branch.Equals(branch2)) index6 = index;
            //Console.WriteLine("{0} {1}", index, branch.ToString());
            index++;
        }

        Console.WriteLine("Decoder key {0}", index2 * index6);
    }
}