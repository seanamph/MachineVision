bool MLP::training(unsigned char* samples, int input_feature_vector, char* trainer_string, int num)
{
    initVariable();

    formNetwork();
    initializeWeights();

    BYTE** list0 = create2DList(samples, num, input_feature_vector);
    formInputSet(list0, num);
    formDesiredOutputSet(trainer_string);

    trainNetwork();

    m_training_flag = true;
    release2DList(list0);
    return true;
}

bool MLP::classify(unsigned char* sample, char *output_char)
{
    if (m_training_flag == false || sample == NULL)
        return false;

    m_config.number_of_input_sets = 1;

    for (int i = 0; i < m_config.number_of_input_nodes; i++)
    {
        m_input_nodes[i].input_set[0] = sample[i] / 255.0;
    }

    getInputs(0);
    calculateOutputs();

    int dec = 0;
    for (int i = 0; i < 8; i++)
    {
        m_output_nodes[i].output_bit = threshold(m_layers[m_config.number_of_layers - 1].node_output[i]);
       
        dec = dec + m_output_nodes[i].output_bit * (int)(pow(2, i));
    }

    *output_char = (char)dec;    
    return true;
}

void MLP::formDesiredOutputSet(std::string trainer_string)
{
    for (int i = 0; i < m_config.number_of_input_sets; i++)
    {
        char data = trainer_string.c_str()[i];
        characterToUnicode(std::string(&data));
        for (int j = 0; j < m_config.number_of_output_nodes; j++)
            m_output_nodes[j].desired_set[i] = m_output_nodes[j].desired_output_bit;
    }
}

void MLP::characterToUnicode(std::string character)
{
    const size_t cSize = strlen(character.c_str()) + 1;
    wchar_t* wc = new wchar_t[cSize];
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wc, cSize, character.c_str(), _TRUNCATE);
   
    int bit_array_length = convertedChars * 16;
    bit_array_length = bit_array_length > m_config.number_of_output_nodes ? m_config.number_of_output_nodes : bit_array_length;
   
    for (int i = 0; i < bit_array_length; i++)
    {
        if (((wc[(i / 16)] >> (i % 16)) & 0x0001) == 0x0001)        
            m_output_nodes[i].desired_output_bit = 1;                   
        else
            m_output_nodes[i].desired_output_bit = 0;        
    }
   
    delete[] wc;
}