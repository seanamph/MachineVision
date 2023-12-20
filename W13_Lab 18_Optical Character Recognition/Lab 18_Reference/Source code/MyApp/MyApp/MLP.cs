using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;



namespace Perceptron
{
    class MLP
    {
        const int number_of_layers = 3;                     //3
        const int number_of_input_nodes =  150;             //150
        const int number_of_output_nodes = 16;              //16
        const int maximum_layers = 250;                     //250
        const int maximum_number_of_sets = 100;             //100
        int number_of_input_sets;
        int epochs = 600;                                   //600
        const double error_threshold = 0.0002;              //0.0002F


        double learning_rate = 150;                          //150F
        double slope = 0.014;                                //0.014F	
        int weight_bias = 30;                                //30

        int[] layers = new int[number_of_layers];
        double[] current_input = new double[number_of_input_nodes];
        double[,] input_set = new double[number_of_input_nodes, maximum_number_of_sets];
        int[] desired_output = new int[number_of_output_nodes];
        int[,] desired_output_set = new int[number_of_output_nodes, maximum_number_of_sets];
        double[,] node_output = new double[number_of_layers, maximum_layers];
        double[,,] weight = new double[number_of_layers, maximum_layers, maximum_layers];
        double[,] error = new double[number_of_layers, maximum_layers];
        int[] output_bit = new int[number_of_output_nodes];
        int[] desired_output_bit = new int[number_of_output_nodes];

        bool training_flag = false;

        Random rnd = new Random();

        UnicodeEncoding unicode = new UnicodeEncoding();

        public bool Training(Byte[,] samples, string trainer_string, int num)
        {
           
            form_network();
            initialize_weights();
            form_input_set(samples, num);
            form_desired_output_set(trainer_string);

            train_network();

            training_flag = true;

            return true;
        }

        public string Classify(Byte[] sample)
        {
            if (training_flag == false)
                return null;

            number_of_input_sets = 1;

            for (int i = 0; i < number_of_input_nodes; i++)
            {
                /*if (sample[i] > 0)
                    input_set[i, 0] = 1;
                else 
                    input_set[i, 0] = 0;*/

                input_set[i, 0] = sample[i]/255.0;
            }
                

            get_inputs(0);
            calculate_outputs();

            int dec = 0;
            for (int i = 0; i < 8; i++)
            {
                output_bit[i] = threshold(node_output[number_of_layers - 1, i]);
                dec = dec + output_bit[i] * (int)(Math.Pow(2, i));
            }

            char output_char = (char)dec;

            return (output_char.ToString());
        }

        public bool Save_Network(StreamWriter network_save_file_stream)
        {
            network_save_file_stream.WriteLine("MLP Weight values. 2022 NTUT Embedded Machine Vision. ");
            network_save_file_stream.WriteLine("Network Name	= OCR Test");
            network_save_file_stream.WriteLine("Hidden Layer Size	= " + maximum_layers.ToString());
            network_save_file_stream.WriteLine("Number of Patterns= " + number_of_input_sets.ToString());
            network_save_file_stream.WriteLine("Number of Epochs	= " + epochs.ToString());
            network_save_file_stream.WriteLine("Learning Rate	= " + learning_rate.ToString());
            network_save_file_stream.WriteLine("Sigmoid Slope	= " + slope.ToString());
            network_save_file_stream.WriteLine("Weight Bias	= " + weight_bias.ToString());
            network_save_file_stream.WriteLine("");

            for (int i = 1; i < number_of_layers; i++)
            {
                for (int j = 0; j < layers[i]; j++)
                {
                    for (int k = 0; k < layers[i - 1]; k++)
                    {
                        network_save_file_stream.Write("Weight[" + i.ToString() + " , " + j.ToString() + " , " + k.ToString() + "] = ");
                        network_save_file_stream.WriteLine(weight[i, j, k]);
                    }
                }
            }
            return true;
        }

        public bool Load_Network(StreamReader network_load_file_stream)
        {
            form_network();

            string weight_text = "";
            string line;
            char[] weight_char = new char[20];
           
            int title_length, weight_length;

            for (int i = 0; i < 9; i++)
                network_load_file_stream.ReadLine();

            for (int i = 1; i < number_of_layers; i++)
            {
                for (int j = 0; j < layers[i]; j++)
                {
                    for (int k = 0; k < layers[i - 1]; k++)
                    {
                        weight_text = "";
                        line = network_load_file_stream.ReadLine();
                        title_length = ("Weight[" + i.ToString() + " , " + j.ToString() + " , " + k.ToString() + "] = ").Length;
                        weight_length = line.Length - title_length;
                        line.CopyTo(title_length, weight_char, 0, weight_length);

                        for (int counter = 0; counter < weight_length; counter++)
                            weight_text = weight_text + weight_char[counter].ToString();

                        weight[i, j, k] = (double)Convert.ChangeType(weight_text, typeof(double));
                    }
                }
            }

            training_flag = true;

            return true;
        }

        private void form_network()
        {
            layers[0] = number_of_input_nodes;
            layers[number_of_layers - 1] = number_of_output_nodes;
            for (int i = 1; i < number_of_layers - 1; i++)
                layers[i] = maximum_layers;
        }

        private void initialize_weights()
        {
            for (int i = 1; i < number_of_layers; i++)
                for (int j = 0; j < layers[i]; j++)
                    for (int k = 0; k < layers[i - 1]; k++)
                        weight[i, j, k] = (double)(rnd.Next(-weight_bias, weight_bias));
        }

        private void form_input_set(Byte[,] samples, int num)
        {
            number_of_input_sets = num;
            for (int i = 0; i < num; i++)
            {
                for (int j = 0; j < number_of_input_nodes; j++)
                {
                  /*if (samples[j, i] > 0)
                        input_set[j, i] = 1;
                    else
                        input_set[j, i] = 0;*/

                    input_set[j, i] = samples[j, i]/255.0; 
                }
            }    
        }

        private void form_desired_output_set(string trainer_string)
        {
            for (int i = 0; i < number_of_input_sets; i++)
            {
                character_to_unicode(trainer_string[i].ToString());
                for (int j = 0; j < number_of_output_nodes; j++)
                    desired_output_set[j, i] = desired_output_bit[j];
            }
        }

        private void train_network()
        {
            int set_number;
            float average_error = 0.0F;
            for (int epoch = 0; epoch <= epochs; epoch++)
            {
                average_error = 0.0F;
                for (int i = 0; i < number_of_input_sets; i++)
                {
                    set_number = rnd.Next(0, number_of_input_sets);
                    //set_number = i;
                    get_inputs(set_number);
                    get_desired_outputs(set_number);
                    calculate_outputs();
                    calculate_errors();
                    calculate_weights();
                    average_error = average_error + get_average_error();
                }
               
                average_error = average_error / number_of_input_sets;
                if (average_error < error_threshold)
                {
                    epoch = epochs + 1;
                   
                }
            }
       
        }

        private void get_inputs(int set_number)
        {
            for (int i = 0; i < number_of_input_nodes; i++)
                current_input[i] = input_set[i, set_number];
        }

        private void get_desired_outputs(int set_number)
        {
            for (int i = 0; i < number_of_output_nodes; i++)
                desired_output[i] = desired_output_set[i, set_number];
        }

        private void calculate_outputs()
        {
            double f_net;
            int number_of_weights;
            for (int i = 0; i < number_of_layers; i++)
            {
                for (int j = 0; j < layers[i]; j++)
                {
                    f_net = 0.0F;
                    if (i == 0) number_of_weights = 1;
                    else number_of_weights = layers[i - 1];

                    for (int k = 0; k < number_of_weights; k++)
                    {
                        if (i == 0)
                            f_net = current_input[j];
                        else
                            f_net = f_net + node_output[i - 1, k] * weight[i, j, k];
                    }

                    node_output[i, j] = sigmoid(f_net);
                }
            }
        }

        private double sigmoid(double f_net)
        {
            //float result=(float)(1/(1+Math.Exp (-1*slope*f_net)));		//Unipolar
            float result = (float)((2 / (1 + Math.Exp(-1 * slope * f_net))) - 1);       //Bipolar			
            return result;
        }

        private double sigmoid_derivative(double result)
        {
            //float derivative=(float)(result*(1-result));					//Unipolar
            double derivative = (double)(0.5F * (1 - Math.Pow(result, 2)));           //Bipolar			
            return derivative;
        }

        private int threshold(double val)
        {
            if (val < 0.5)
                return 0;
            else
                return 1;
        }

        private void calculate_errors()
        {
            double sum = 0.0F;
            for (int i = 0; i < number_of_output_nodes; i++)
                error[number_of_layers - 1, i] = (float)((desired_output[i] - node_output[number_of_layers - 1, i]) * sigmoid_derivative(node_output[number_of_layers - 1, i]));

            for (int i = number_of_layers - 2; i >= 0; i--)
            {
                for (int j = 0; j < layers[i]; j++)
                {
                    sum = 0.0F;
                    for (int k = 0; k < layers[i + 1]; k++)
                        sum = sum + error[i + 1, k] * weight[i + 1, k, j];
                    error[i, j] = (double)(sigmoid_derivative(node_output[i, j]) * sum);
                }
            }
        }

        private float get_average_error()
        {
            double average_error = 0.0F;
            for (int i = 0; i < number_of_output_nodes; i++)
                average_error = average_error + error[number_of_layers - 1, i];
            average_error = average_error / number_of_output_nodes;
            return Math.Abs((float)average_error);
        }

        private void calculate_weights()
        {
            for (int i = 1; i < number_of_layers; i++)
                for (int j = 0; j < layers[i]; j++)
                    for (int k = 0; k < layers[i - 1]; k++)
                    {
                        weight[i, j, k] = (float)(weight[i, j, k] + learning_rate * error[i, j] * node_output[i - 1, k]);
                    }
        }

        private void character_to_unicode(string character)
        {
            int byteCount = unicode.GetByteCount(character.ToCharArray());
            byte[] bytes = new Byte[byteCount];
            bytes = unicode.GetBytes(character);
            BitArray bits = new BitArray(bytes);
            int bit_array_length = bits.Length;

            for (int i = 0; i < bit_array_length; i++)
            { 
                if (bits[i])
                    desired_output_bit[i] = 1;
                else
                    desired_output_bit[i] = 0;
            }

        }

    }
}
