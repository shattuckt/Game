using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetEdit
{
    public enum NeuronType
    {
        Input = 1,
        Hiden = 2,
        Output = 3
    }

    public class AddNeuronEventArgs : EventArgs
    {
        public string Name { get; set; }
        public NeuronType NeuronType { get; set; }
    }

    public class AddSynapseEventArgs : EventArgs
    {
        public double Weight { get; set; }
        public int Start { get; set; }
        public int Target { get; set; }
    }
}
