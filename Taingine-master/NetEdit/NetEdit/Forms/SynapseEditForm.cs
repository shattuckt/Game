using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NetEdit.Forms
{
    public partial class SynapseEditForm : MovableResizableForm
    {
        private int position;

        public SynapseEditForm()
        {
            InitializeComponent();
            var activeNeuron = EditorHelper.ActiveNeuron;
            position = activeNeuron.ArrPosition;
            switch (activeNeuron.NeuronType)
            {
                case NeuronType.Output:
                    position += Network.InputTags.Count;
                    break;
                case NeuronType.Hiden:
                    position += Network.InputTags.Count + Network.OutputTags.Count;
                    break;
            }

            var dict = new Dictionary<string, Trait>();
            foreach(var trait in Network.Traits)
            {
                if(trait.Start == position)
                {
                    //synapseSelectionComboBox.Items.Add(trait.Target);
                    dict.Add($"{trait.Target}", trait);
                }
            }

            synapseSelectionComboBox.DataSource = new BindingSource(dict, null);
            synapseSelectionComboBox.DisplayMember = "Key";
            synapseSelectionComboBox.ValueMember = "Value";
        }

        private void ChangeButton_Click(object sender, EventArgs e)
        {
            var pair = (KeyValuePair<string, Trait>)synapseSelectionComboBox.SelectedItem;
            //int i = 0;
            //foreach (var trait in Network.Traits)
            //{
            //    if (trait.Start == position && trait.Target == pair.Value.Target)
            //    {
            //        break;
            //    }
            //    i++;
            //}

            //Trait chageTrait = Network.Traits.ElementAt(position);
            //chageTrait.Weight = Double.Parse(newValueTextBox.Text);
            pair.Value.Weight = double.Parse(newValueTextBox.Text);
        }

        private void SynapseSelectionComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var pair = (KeyValuePair<string, Trait>)synapseSelectionComboBox.SelectedItem;
            weightLabel.Text = $"{pair.Value.Weight}";
        }
    }
}
