#ifndef LLAMA_H
#define LLAMA_H
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t llama_token;
typedef int32_t llama_pos;
typedef int32_t llama_seq_id;

typedef struct llama_model { int dummy; } llama_model;
typedef struct llama_context { int dummy; } llama_context;
typedef struct llama_sampler { int dummy; } llama_sampler;

typedef struct {
    int32_t n_gpu_layers;
} llama_model_params;

typedef struct {
    int32_t n_ctx;
    int32_t n_threads;
    int32_t n_threads_batch;
} llama_context_params;

typedef struct llama_batch {
    int32_t n_tokens;
    llama_token * token;
    llama_pos   * pos;
    int32_t     * n_seq_id;
    llama_seq_id ** seq_id;
    uint8_t     * logits;
} llama_batch;

typedef struct {
    int dummy;
} llama_sampler_params;

void llama_backend_init(void);
void llama_backend_free(void);
llama_model_params llama_model_default_params(void);
llama_context_params llama_context_default_params(void);
llama_model * llama_load_model_from_file(const char * path, llama_model_params params);
llama_context * llama_new_context_with_model(llama_model * model, llama_context_params params);
void llama_free_model(llama_model * model);
void llama_free(llama_context * ctx);
int llama_n_ctx(llama_context * ctx);
int llama_decode(llama_context * ctx, llama_batch batch);
llama_batch llama_batch_init(int size, int seq_capacity, int ctx_capacity);
void llama_batch_free(llama_batch batch);
llama_sampler_params llama_sampler_chain_default_params(void);
llama_sampler * llama_sampler_chain_init(llama_sampler_params params);
void llama_sampler_chain_add(llama_sampler * chain, llama_sampler * sampler);
llama_sampler * llama_sampler_init_temp(float temp);
llama_sampler * llama_sampler_init_softmax(void);
llama_sampler * llama_sampler_init_dist(int seed);
void llama_sampler_free(llama_sampler * sampler);
llama_token llama_sampler_sample(llama_sampler * sampler, llama_context * ctx, int index);
int32_t llama_tokenize(llama_model * model, const char * text, int32_t text_len, llama_token * tokens, int32_t tokens_len, bool add_bos, bool special);
int32_t llama_token_to_piece(llama_model * model, llama_token token, char * buf, int32_t length, int32_t flag, bool special);
bool llama_token_is_eog(llama_model * model, llama_token token);

#ifdef __cplusplus
}
#endif

#endif // LLAMA_H
