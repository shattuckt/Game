using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace NetEdit
{
    public static class EditorHelper
    {

        private static NeuronUserControl _activeNeuron = null;


        public static NeuronUserControl ActiveNeuron
        {
            get => _activeNeuron;
            set
            {
                if(_activeNeuron != null)
                {
                    switch (_activeNeuron.NeuronType)
                    {
                        case NeuronType.Input:
                            Network.InputTags[_activeNeuron.ArrPosition] = _activeNeuron.NeuronTag;
                            break;
                        case NeuronType.Hiden:

                            break;
                        case NeuronType.Output:
                            Network.OutputTags[_activeNeuron.ArrPosition] = _activeNeuron.NeuronTag;
                            break;
                    }
                    //_activeNeuron.BackColor = Color.FromArgb(139, 87, 92);
                    _activeNeuron.NeuronUserControl_ChangeColor();
                }
                    
                _activeNeuron = value;
                AddNeuronEventArgs args = new AddNeuronEventArgs();
                args.Name = _activeNeuron.NeuronTag;
                EventHub.OnChangeText(_activeNeuron, args);
            }
        }

        public static string ActiveNeuronTag
        {
            get => _activeNeuron.NeuronTag;
            set
            {
                _activeNeuron.NeuronTag = value;
                FileHelper.FileHasChanges = true;
            }
        }

        public static void Reset()
        {
            _activeNeuron = null;
        }

    }
}
