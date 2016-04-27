#include <stdio.h>

#include "csvparser.h"

int main()
{
  int i = 0;
  //                                   file, delimiter, first_line_is_header?
  CsvParser* csvparser = CsvParser_new("example_file_with_header.csv", ",", 1);
  CsvRow* header;
  CsvRow* row;

  header = CsvParser_getHeader(csvparser);

  if (header == NULL)
  {
    printf("%s\n", CsvParser_getErrorMessage(csvparser));
    return 1;
  }

  const char** headerFields = CsvParser_getFields(header);

  for (i = 0; i < CsvParser_getNumFields(header); i++)
  {
    printf("TITLE: %s\n", headerFields[i]);
  }

  // Do NOT destroy the header manually if you plan to destroy the parser later.
  // If you destroy both header and parser, you will get double free runtime error
  // CsvParser_destroy_row(header);
  while ((row = CsvParser_getRow(csvparser)))
  {
    printf("==NEW LINE==\n");

    const char** rowFields = CsvParser_getFields(row);

    for (i = 0; i < CsvParser_getNumFields(row); i++)
    {
      printf("FIELD: %s\n", rowFields[i]);
    }

    printf("\n");
    CsvParser_destroy_row(row);
  }

  CsvParser_destroy(csvparser);

  return 0;
}