#include "eml_net.h" //#include "emlearn/eml_net.h"
static const float nevronskaMreza_jakostGibanja_layer0_weights[10] = { -52.627436f, 30.059037f, -28.388565f, -32.217697f, -41.622031f, 10.073207f, 45.367257f, 4.219636f, 52.018412f, -13.977721f };
static const float nevronskaMreza_jakostGibanja_layer0_biases[10] = { -17.204247f, 18.920001f, -17.194527f, -31.730535f, -32.081091f, 11.695047f, 33.897374f, -11.039940f, 26.402142f, -7.027614f };
static const float nevronskaMreza_jakostGibanja_layer1_weights[30] = { 56.311325f, -26.739436f, -28.783008f, -42.850668f, 17.868233f, 26.287216f, 63.129695f, -20.615697f, -44.147577f, 10.833236f, -1.879026f, -9.092911f, 69.735372f, -28.229340f, -40.581025f, 11.367387f, 6.996397f, -17.907814f, -8.128481f, 15.290753f, -6.813777f, -4.537137f, 5.795465f, -0.827759f, -18.992514f, 13.470552f, 5.467397f, 22.672234f, -14.054931f, -9.685409f };
static const float nevronskaMreza_jakostGibanja_layer1_biases[3] = { -36.026299f, 22.717305f, 12.507112f };
static float nevronskaMreza_jakostGibanja_buf1[10];
static float nevronskaMreza_jakostGibanja_buf2[10];
static const EmlNetLayer nevronskaMreza_jakostGibanja_layers[2] = { 
{ 10, 1, nevronskaMreza_jakostGibanja_layer0_weights, nevronskaMreza_jakostGibanja_layer0_biases, EmlNetActivationIdentity }, 
{ 3, 10, nevronskaMreza_jakostGibanja_layer1_weights, nevronskaMreza_jakostGibanja_layer1_biases, EmlNetActivationSoftmax } };
static EmlNet nevronskaMreza_jakostGibanja = { 2, nevronskaMreza_jakostGibanja_layers, nevronskaMreza_jakostGibanja_buf1, nevronskaMreza_jakostGibanja_buf2, 10 };

    int32_t
    nevronskaMreza_jakostGibanja_predict(const float *features, int32_t n_features)
    {
        return eml_net_predict(&nevronskaMreza_jakostGibanja, features, n_features);

    }
    
