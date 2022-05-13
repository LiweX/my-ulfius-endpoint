#include <stdio.h>
#include <ulfius.h>
#include <string.h>

#define PORT 8537

int valor=0;

int callback_increment (const struct _u_request * request, struct _u_response * response, void * user_data) {
    request=request;
    user_data=user_data;
    valor++;
    ulfius_set_string_body_response(response, 200, "incremented!\n");
    return U_CALLBACK_CONTINUE;
}

int callback_imprimir (const struct _u_request * request, struct _u_response * response, void * user_data) {
    request=request;
    user_data=user_data;
    int length = snprintf( NULL, 0, "%d", valor );
    char* str = malloc( (size_t)(length + 2) );
    sprintf(str, "%d", valor );
    strcat(str,"\n");
    ulfius_set_string_body_response(response, 200, str);
    free(str);
    return U_CALLBACK_CONTINUE;
}

/**
 * main function
 */
int main(void) {
  struct _u_instance instance;

  // Initialize instance with the port number
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return(1);
  }

  // Endpoint list declaration
  ulfius_add_endpoint_by_val(&instance, "POST", "/increment", NULL, 0, &callback_increment, NULL);
  ulfius_add_endpoint_by_val(&instance, "GET", "/imprimir", NULL, 0, &callback_imprimir, NULL);

  // Start the framework
  if (ulfius_start_framework(&instance) == U_OK) {
    printf("Start framework on port %d\n", instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  } else {
    fprintf(stderr, "Error starting framework\n");
  }
  printf("End framework\n");

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  return 0;
}
