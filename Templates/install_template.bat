if not exist "C:\Users\%USERNAME%\Documents\Visual Studio 2022\Templates\ProjectTemplates\My Exported Templates" (
    mkdir "C:\Users\%USERNAME%\Documents\Visual Studio 2022\Templates\ProjectTemplates\My Exported Templates"
)

copy .\* "C:\Users\%USERNAME%\Documents\Visual Studio 2022\Templates\ProjectTemplates\My Exported Templates"

pause
