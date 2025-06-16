#include "llama.h"
#include <stdlib.h>

void llama_backend_init(void) {}
void llama_backend_free(void) {}

llama_model_params llama_model_default_params(void) {
    llama_model_params p; p.n_gpu_layers = 0; return p;
}

llama_context_params llama_context_default_params(void) {
    llama_context_params p; p.n_ctx = 0; p.n_threads = 0; p.n_threads_batch = 0; return p;
}

llama_model * llama_load_model_from_file(const char * path, llama_model_params params) {
    return (llama_model *)malloc(1);
}

llama_context * llama_new_context_with_model(llama_model * model, llama_context_params params) {
    return (llama_context *)malloc(1);
}

void llama_free_model(llama_model * model) { free(model); }
void llama_free(llama_context * ctx) { free(ctx); }
int llama_n_ctx(llama_context * ctx) { return 0; }

int llama_decode(llama_context * ctx, llama_batch batch) { return 0; }

llama_batch llama_batch_init(int size, int seq_capacity, int ctx_capacity) {
    llama_batch b; b.n_tokens = 0;
    b.token = calloc(size, sizeof(llama_token));
    b.pos = calloc(size, sizeof(llama_pos));
    b.n_seq_id = calloc(size, sizeof(int32_t));
    b.seq_id = calloc(size, sizeof(llama_seq_id*));
    for (int i=0;i<size;i++) b.seq_id[i] = calloc(seq_capacity, sizeof(llama_seq_id));
    b.logits = calloc(size, sizeof(uint8_t));
    return b;
}

void llama_batch_free(llama_batch batch) {
    free(batch.token);
    free(batch.pos);
    free(batch.n_seq_id);
    if(batch.seq_id){
        // free nested arrays? simplistic free
        free(batch.seq_id);
    }
    free(batch.logits);
}

llama_sampler_params llama_sampler_chain_default_params(void) {
    llama_sampler_params p; p.dummy = 0; return p;
}

llama_sampler * llama_sampler_chain_init(llama_sampler_params params) {
    return (llama_sampler *)malloc(1);
}

void llama_sampler_chain_add(llama_sampler * chain, llama_sampler * sampler) {}
llama_sampler * llama_sampler_init_temp(float temp) { return (llama_sampler *)malloc(1); }
llama_sampler * llama_sampler_init_softmax(void) { return (llama_sampler *)malloc(1); }
llama_sampler * llama_sampler_init_dist(int seed) { return (llama_sampler *)malloc(1); }
void llama_sampler_free(llama_sampler * sampler) { free(sampler); }
llama_token llama_sampler_sample(llama_sampler * sampler, llama_context * ctx, int index) { return 0; }
int32_t llama_tokenize(llama_model * model, const char * text, int32_t text_len, llama_token * tokens, int32_t tokens_len, bool add_bos, bool special) { return 0; }
int32_t llama_token_to_piece(llama_model * model, llama_token token, char * buf, int32_t length, int32_t flag, bool special) { return 0; }
bool llama_token_is_eog(llama_model * model, llama_token token) { return false; }

