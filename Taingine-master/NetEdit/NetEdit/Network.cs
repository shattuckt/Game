using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace NetEdit
{
    public static class Network
    {
        #region Constants

        private const string DEFAULT_HEADER = "TANN";
        private const byte DEFAULT_VERSION = 2;
        private const uint DEFAULT_GENERATION = 0;

        #endregion

        #region Private Members

        private static string _header;
        private static byte _version;
        private static uint _generation;

        //private static uint _numberInputNeurons;
        private static List<string> _inputTags;
        //private static uint _numberOutputNeurons;
        private static List<string> _outputTags;
        private static uint _numberHidinNeurons = 0;

        private static List<Trait> _traits;

        private static int highestInnovationNum = 0;

        #endregion

        #region Public Members

        public static string Header
        {
            get => _header;
            set => _header = value;
        }

        public static byte Version
        {
            get => _version;
            set => _version = value;
        }

        public static uint Generation
        {
            get => _generation;
            set => _generation = value;
        }
        public static List<string> InputTags
        {
            get => _inputTags;
            set => _inputTags = value;
        }

        public static List<string> OutputTags
        {
            get => _outputTags;
            set => _outputTags = value;
        }

        public static uint NumberHidinNeurons
        {
            get => _numberHidinNeurons;
            set => _numberHidinNeurons = value;
        }

        public static List<Trait> Traits
        {
            get => _traits;
            set => _traits = value;
        }

        public static int CurrentInnovationLimit
        {
            get => _traits.ElementAt(_traits.Count - 1).InnovationNumber;
        }

        #endregion

        static Network()
        {
            _inputTags = new List<string>();
            _outputTags = new List<string>();
            _traits = new List<Trait>();
        }

        #region Load File

        public static void LoadNetwork(String filePath)
        {
            BinaryReader reader = new BinaryReader(new FileStream(filePath, FileMode.Open));

            _header = new string(reader.ReadChars(4));
            _version = reader.ReadByte();
            _generation = reader.ReadUInt32();

             uint numberInputNeurons = reader.ReadUInt32();
            _inputTags = LoadStringList(numberInputNeurons, reader);

            uint numberOutputNeurons = reader.ReadUInt32();
            _outputTags = LoadStringList(numberOutputNeurons, reader);

            _numberHidinNeurons = reader.ReadUInt32();

            uint numberOfTraits = reader.ReadUInt32();
            for (uint i = 0; i < numberOfTraits; i++)
            {
                _traits.Add(LoadTrait(reader));
            }

            highestInnovationNum = _traits.Count;

            reader.Close();
        }


        private static List<string> LoadStringList(uint count, BinaryReader reader)
        {
            List<string> returnValue = new List<string>();
            for (uint i = 0; i < count; i++)
            {
                int size = reader.ReadInt32();
                returnValue.Add(new string(reader.ReadChars(size)));
            }

            return returnValue;
        }


        private static Trait LoadTrait(BinaryReader reader)
        {
            int start = reader.ReadInt32();
            int target = reader.ReadInt32();
            double weight = reader.ReadDouble();
            int innovationNumber = reader.ReadInt32();
            bool isDisabled = reader.ReadBoolean();
            Trait trait = new Trait(start, target, weight, innovationNumber, isDisabled);

            return trait;
        }

        #endregion

        #region Write File
        public static void WriteNetwork(String filePath)
        {
            BinaryWriter writer = new BinaryWriter(new FileStream(filePath, FileMode.Create));

            if (String.IsNullOrEmpty(_header))
            {
                _header = DEFAULT_HEADER;
                _version = DEFAULT_VERSION;
                _generation = DEFAULT_GENERATION;
            }

            writer.Write(_header.ToCharArray());
            writer.Write(_version);
            writer.Write(_generation);

            writer.Write(_inputTags.Count);
            WriteStringList(_inputTags, writer);

            writer.Write(_outputTags.Count);
            WriteStringList(_outputTags, writer);

            writer.Write(_numberHidinNeurons);

            writer.Write(_traits.Count);
            WriteTraitList(_traits, writer);

            writer.Close();
        }


        private static void WriteStringList(List<string> list, BinaryWriter writer)
        {
            foreach(string tag in list)
            {
                writer.Write(tag.Length);
                writer.Write(tag.ToCharArray());
            }
        }


        private static void WriteTraitList(List<Trait> traits, BinaryWriter writer)
        {
            foreach(Trait trait in traits)
            {
                writer.Write(trait.Start);
                writer.Write(trait.Target);
                writer.Write(trait.Weight);
                writer.Write(trait.InnovationNumber);
                writer.Write(trait.IsDisabled);
            }
        }
        #endregion


        public static void InitilizeEvents()
        {
            EventHub.AddNeuron += AddNeuronToNetwork;
            EventHub.AddSynapse += AddSynapseToNetwork;
        }


        public static void AddNeuronToNetwork(object sender, AddNeuronEventArgs eventArgs)
        {
            Random random = new Random();
            switch (eventArgs.NeuronType)
            {
                case NeuronType.Input:
                    InputTags.Add(eventArgs.Name);

                    for (int i = 0; i < _outputTags.Count; i++)
                    {
                        Trait trait = new Trait(_inputTags.Count - 1, i, random.NextDouble(), ++highestInnovationNum, false);
                        _traits.Add(trait);
                    }

                    break;
                case NeuronType.Hiden:
                    NumberHidinNeurons += 1;
                    break;
                case NeuronType.Output:
                    OutputTags.Add(eventArgs.Name);

                    for (int i = 0; i < _inputTags.Count; i++)
                    {
                        Trait trait = new Trait(i, _inputTags.Count + _outputTags.Count - 1, random.NextDouble(), ++highestInnovationNum, false);
                        _traits.Add(trait);
                    }
                    break;
            }
        }


        public static void AddSynapseToNetwork(object sender, AddSynapseEventArgs eventArgs)
        {
            Trait trait = new Trait(eventArgs.Start, eventArgs.Target, eventArgs.Weight, ++highestInnovationNum, false);
            _traits.Add(trait);
        }


        public static void Clear()
        {
            _inputTags.Clear();
            _outputTags.Clear();
            _traits.Clear();
        }
    }
}
