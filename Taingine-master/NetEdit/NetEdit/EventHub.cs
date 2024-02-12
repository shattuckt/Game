using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetEdit
{
    public static class EventHub
    {
        public static event EventHandler<AddNeuronEventArgs> AddNeuron;
        public static event EventHandler<AddNeuronEventArgs> ChangeText;
        public static event EventHandler<AddSynapseEventArgs> AddSynapse;
        public static event EventHandler<EventArgs> LoadNeuronView;


        public static void OnLoadNeuronView(object sender, EventArgs eventArgs)
        {
            LoadNeuronView?.Invoke(sender, eventArgs);
        }

        public static void OnAddNeuron(object sender, AddNeuronEventArgs eventArgs)
        {
            FileHelper.FileHasChanges = true;
            AddNeuron?.Invoke(sender, eventArgs);
        }

        public static void OnAddSynapse(object sender, AddSynapseEventArgs eventArgs)
        {
            FileHelper.FileHasChanges = true;
            AddSynapse?.Invoke(sender, eventArgs);
        }

        public static void OnChangeText(object sender, AddNeuronEventArgs eventArgs)
        {
            ChangeText?.Invoke(sender, eventArgs);
        }
    }
}
