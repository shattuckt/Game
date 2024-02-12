using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NetEdit
{
    public static class FileHelper
    {
        #region Private Members

        private static bool _fileIsOpen = false;
        private static bool _fileHasChanges = false;
        private static string _filePath = "";
        private static SaveFileDialog _saveDialog;

        #endregion

        #region Public Members

        public static bool FileIsOpen
        {
            get => _fileIsOpen;
            set => _fileIsOpen = value;
        }


        public static string FilePath
        {
            get => _filePath;
            set => _filePath = value;
        }


        public static bool FileHasChanges
        {
            get => _fileHasChanges;
            set => _fileHasChanges = value;
        }

        #endregion


        static FileHelper()
        {
            _saveDialog = new SaveFileDialog();
            _saveDialog.Filter = "Network Files|*.nn";
            _saveDialog.RestoreDirectory = true;
        }


        public static void SaveFile()
        {
            if (String.IsNullOrEmpty(FilePath))
            {
                SaveFileAs();
            }
            else
            {
                Network.WriteNetwork(FilePath);
            }

            _fileHasChanges = false;
        }


        public static void SaveFileAs()
        {
            DialogResult result = _saveDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                string fileLocation = _saveDialog.FileName;

                if (!fileLocation.EndsWith(".nn"))
                {
                    fileLocation += ".nn";
                }

                if (String.IsNullOrEmpty(fileLocation) ||
                System.IO.File.Exists(fileLocation))
                {
                    return;
                }

                FilePath = fileLocation;
                SaveFile();
            }
        }


        public static DialogResult CheckFileStatus()
        {
            if (FileHasChanges)
            {
                using (var form = new SaveChangesPopup())
                {
                    DialogResult result = form.ShowDialog();
                    switch (result)
                    {
                        case DialogResult.Yes:
                            SaveFile();
                            CloseFile();
                            return DialogResult.OK;
                        case DialogResult.No:
                            CloseFile();
                            return DialogResult.OK;
                        default:
                            return DialogResult.Cancel;
                    }
                }
            }
            else
            {
                return DialogResult.OK;
            }
        }


        public static void OpenFile(string path)
        {
            FileIsOpen = true;
            FilePath = path;
            Network.LoadNetwork(path);
        }


        public static void CloseFile()
        {
            FileIsOpen = false;
            FileHasChanges = false;
            Network.Clear();
            FilePath = "";
        }

    }
}
