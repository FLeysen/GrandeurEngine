-----------------------
-- Engine Features --
-----------------------
-- Input --
- Uses linking of commands and mappings
- Allows keyboard, controller button and controller axis mapping
- Multiple inputs can be assigned to same command, multiple commands can be assigned to the same input
- Any amount of players

-- Collision --
- Layer-based
- Allows layer ignores
- Colliders have a function holder, called when overlapping with a non-ignored collider

-- GameObject --
- Can be set active/inactive to enable/disable updating of components
- Uses string tags, comparison uses values instead of strings
- Always has a transform
- Holds its components to update and destroy them
- Components can freely be removed (by object or by type) or added
- Components can be retrieved by type

-- Components --
- All have an update and pointer to the object they are attached to
- Can implement function ShouldDelete if anything other than the object it's attached to should manage it

-- Menuing --
- Menu component keeps track of buttons
- Buttons have a function holder, called when pressed

-- Rendering --
- Scene manages its renderers
- Renderers are in a large container to ensure faster rendering
- Sprites support all sorts of transformations

-- States --
- State component using dynamic states
- States allocate next state when needed, notify state component

-- Observer-Subject --
- User-defined events (as unsigned integer)
- Subject knows its observers, notifies them

-- Utilities --
- Text localizer using csv, also used to gather texture paths
- Invoker: class holding functions which are called after a set interval (possibly repeatedly), supports cancelling of invokes "owned" by an object
- Logging system with timestamps, three log types
- Time class, holding deltatime, fixed time, total time, supports time scale
- Resource manager, holding all textures and fonts, fonts and textures are retrieved with their names
- Button prefab to easily add buttons to scene
- Simple free mover allowing acceleration, regular velocity and starting/stopping
- Simple grid with gridmover allowing movement along the grid
- Text component that generates textures from strings, requires rendercomponent
- FPS counter component which uses text component to display FPS
