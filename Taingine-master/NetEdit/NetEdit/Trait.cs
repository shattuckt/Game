using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetEdit
{
    public class Trait
    {
        #region Private Members
        private int _start;
        private int _target;
        private double _weight;
        private int _innovationNumber;
        private bool _isDisabled;
        #endregion

        #region Public Members
        public int Start
        {
            get => _start;
            set => _start = value;
        }

        public int Target
        {
            get => _target;
            set => _target = value;
        }

        public double Weight
        {
            get => _weight;
            set => _weight = value;
        }

        public int InnovationNumber
        {
            get => _innovationNumber;
            set => _innovationNumber = value;
        }

        public bool IsDisabled
        {
            get => _isDisabled;
            set => _isDisabled = value;
        }
        #endregion

        public Trait(int start, int target, double weight, int innovationNumber, bool isDisabled)
        {
            _start = start;
            _target = target;
            _weight = weight;
            _innovationNumber = innovationNumber;
            _isDisabled = isDisabled;
        }

    }
}
